// minus devkit — RP2354A "manager" firmware, step 1: inter-MCU link bring-up.
//
// What it does
//   * USB-C CDC console (115200 8N1 virtual, any baud) with a tiny command line.
//   * UART0 (GPIO16 TX / GPIO17 RX) <-> PIC32AK UART1 at 115200 8N1: "PING n\n" -> "PONG n\n".
//   * TRIG (GPIO6, out), RDY (GPIO7, in) GPIO handshake lines.
//   * PIC MCLR tap on GPIO24: Hi-Z by default, "reset" pulses it low (see note on R53).
//   * PIC PGC1/PGD1 taps on GPIO21/22: kept Hi-Z (inputs, no pulls) so a PICkit on J1 works.
//   * RGB status LED (U5 + LED1 in parallel on GPIO10): blue = no PIC, green = link ok, red = bad reply.
//
// Commands (type on the USB console):  help | ping | auto | stop | reset | rdy | trig | raw <text> | stat
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"

#define LINK_UART      uart0
#define LINK_BAUD      115200
#define LINK_TIMEOUT_US 200000   // 200 ms: PIC runs from its 8 MHz FRC, reply is ~1 ms

static uint32_t stat_sent, stat_ok, stat_bad, stat_timeout;
static bool auto_ping = false;
static PIO led_pio; static uint led_sm;

// ---------------------------------------------------------------- RGB status LED
static void led_init(void) {
    led_pio = pio0; led_sm = 0;
    uint off = pio_add_program(led_pio, &ws2812_program);
    ws2812_program_init(led_pio, led_sm, off, MINUS_PIN_RGB, 800000.f);
}
static void led_rgb(uint8_t r, uint8_t g, uint8_t b) {
    // GRB order, left-aligned in the 32-bit FIFO word (out shift = 24 bits, MSB first)
    uint32_t grb = ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;
    pio_sm_put_blocking(led_pio, led_sm, grb << 8);
}

// ---------------------------------------------------------------- link UART helpers
static void link_init(void) {
    uart_init(LINK_UART, LINK_BAUD);
    gpio_set_function(MINUS_PIN_UART_TX, GPIO_FUNC_UART);
    gpio_set_function(MINUS_PIN_UART_RX, GPIO_FUNC_UART);
    uart_set_format(LINK_UART, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(LINK_UART, true);
}
static void link_flush_rx(void) { while (uart_is_readable(LINK_UART)) (void)uart_getc(LINK_UART); }
static void link_puts(const char *s) { uart_puts(LINK_UART, s); }

// read one '\n'-terminated line (without the newline) within timeout; returns length or -1
static int link_readline(char *buf, int max, uint32_t timeout_us) {
    absolute_time_t deadline = make_timeout_time_us(timeout_us);
    int n = 0;
    while (!time_reached(deadline)) {
        if (!uart_is_readable(LINK_UART)) { tight_loop_contents(); continue; }
        char c = uart_getc(LINK_UART);
        if (c == '\r') continue;
        if (c == '\n') { buf[n] = 0; return n; }
        if (n < max - 1) buf[n++] = c;
    }
    buf[n] = 0;
    return -1;
}

// ---------------------------------------------------------------- PIC control taps
static void pic_taps_init(void) {
    // MCLR: Hi-Z (R5 10k pull-up holds the PIC running). Never drive it high: J1/PICkit may.
    gpio_init(MINUS_PIN_PIC_MCLR); gpio_set_dir(MINUS_PIN_PIC_MCLR, GPIO_IN); gpio_disable_pulls(MINUS_PIN_PIC_MCLR);
    // PGC1/PGD1: Hi-Z so an external programmer on J1 is not disturbed.
    gpio_init(MINUS_PIN_PIC_PGC); gpio_set_dir(MINUS_PIN_PIC_PGC, GPIO_IN); gpio_disable_pulls(MINUS_PIN_PIC_PGC);
    gpio_init(MINUS_PIN_PIC_PGD); gpio_set_dir(MINUS_PIN_PIC_PGD, GPIO_IN); gpio_disable_pulls(MINUS_PIN_PIC_PGD);
    // Handshake
    gpio_init(MINUS_PIN_TRIG); gpio_put(MINUS_PIN_TRIG, 0); gpio_set_dir(MINUS_PIN_TRIG, GPIO_OUT);
    gpio_init(MINUS_PIN_RDY);  gpio_set_dir(MINUS_PIN_RDY, GPIO_IN); gpio_disable_pulls(MINUS_PIN_RDY);
}
static void pic_reset(void) {
    // Open-drain style: drive low, then release to Hi-Z. With R53 = 4k7 against R5 = 10k the
    // node only reaches ~1.05 V (PIC VIL max = 0.66 V) -> on the as-built board this is NOT a
    // guaranteed reset. Fit R53 = 0R (or <= 470R) to make it work. See firmware/README.md.
    gpio_set_dir(MINUS_PIN_PIC_MCLR, GPIO_OUT); gpio_put(MINUS_PIN_PIC_MCLR, 0);
    sleep_ms(20);
    gpio_set_dir(MINUS_PIN_PIC_MCLR, GPIO_IN);
}
static void trig_pulse(void) { gpio_put(MINUS_PIN_TRIG, 1); busy_wait_us(2); gpio_put(MINUS_PIN_TRIG, 0); }

// ---------------------------------------------------------------- ping
static bool do_ping(bool verbose) {
    static uint32_t seq = 0;
    char tx[32], rx[64];
    seq++;
    snprintf(tx, sizeof tx, "PING %lu\n", (unsigned long)seq);
    link_flush_rx();
    absolute_time_t t0 = get_absolute_time();
    link_puts(tx);
    stat_sent++;
    int n = link_readline(rx, sizeof rx, LINK_TIMEOUT_US);
    int64_t dt = absolute_time_diff_us(t0, get_absolute_time());
    char want[32]; snprintf(want, sizeof want, "PONG %lu", (unsigned long)seq);
    if (n < 0) { stat_timeout++; led_rgb(0, 0, 40); if (verbose) printf("ping %lu: timeout (%lld us)\n", (unsigned long)seq, dt); return false; }
    if (strcmp(rx, want) == 0) { stat_ok++; led_rgb(0, 40, 0); if (verbose) printf("ping %lu: ok, %lld us, rdy=%d\n", (unsigned long)seq, dt, gpio_get(MINUS_PIN_RDY)); return true; }
    stat_bad++; led_rgb(40, 0, 0);
    if (verbose) printf("ping %lu: bad reply '%s' (%lld us)\n", (unsigned long)seq, rx, dt);
    return false;
}

static void help(void) {
    printf("minus devkit RP2354A link test\n"
           "  ping        send PING n over UART0 (GPIO16/17), expect PONG n from the PIC32\n"
           "  auto|stop   ping every 500 ms / stop\n"
           "  reset       pulse PIC MCLR low via GPIO24 (needs R53 <= 470R, see README)\n"
           "  rdy         read RDY (GPIO7 <- PIC RA7)\n"
           "  trig        2 us pulse on TRIG (GPIO6 -> PIC RA0)\n"
           "  raw <text>  send <text>\\n to the PIC and print whatever comes back within 200 ms\n"
           "  stat        counters\n");
}

int main(void) {
    stdio_init_all();
    led_init(); led_rgb(0, 0, 40);
    pic_taps_init();
    link_init();

    char line[96]; int len = 0;
    absolute_time_t next_auto = get_absolute_time();
    printf("\nminus devkit (hardware/minUS_10102026) RP2354A link test. 'help' for commands.\n");
    while (true) {
        int c = getchar_timeout_us(1000);
        if (c != PICO_ERROR_TIMEOUT) {
            if (c == '\r' || c == '\n') {
                line[len] = 0; len = 0;
                if (!strcmp(line, "help") || !strcmp(line, "?")) help();
                else if (!strcmp(line, "ping")) do_ping(true);
                else if (!strcmp(line, "auto")) { auto_ping = true; printf("auto ping on\n"); }
                else if (!strcmp(line, "stop")) { auto_ping = false; printf("auto ping off\n"); }
                else if (!strcmp(line, "reset")) { pic_reset(); printf("MCLR pulsed\n"); }
                else if (!strcmp(line, "rdy")) printf("RDY=%d\n", gpio_get(MINUS_PIN_RDY));
                else if (!strcmp(line, "trig")) { trig_pulse(); printf("TRIG pulsed\n"); }
                else if (!strncmp(line, "raw ", 4)) {
                    char rx[96]; link_flush_rx(); link_puts(line + 4); link_puts("\n");
                    int n = link_readline(rx, sizeof rx, LINK_TIMEOUT_US);
                    printf(n < 0 ? "no reply ('%s' partial)\n" : "reply: '%s'\n", rx);
                }
                else if (!strcmp(line, "stat")) printf("sent=%lu ok=%lu bad=%lu timeout=%lu\n",
                        (unsigned long)stat_sent, (unsigned long)stat_ok, (unsigned long)stat_bad, (unsigned long)stat_timeout);
                else if (len == 0 && line[0]) printf("unknown '%s' — try help\n", line);
            } else if (len < (int)sizeof line - 1) line[len++] = (char)c;
        }
        if (auto_ping && time_reached(next_auto)) { do_ping(true); next_auto = make_timeout_time_ms(500); }
    }
}
