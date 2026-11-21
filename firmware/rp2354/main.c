// minus v1.1 (board 3) — RP2354A "manager" firmware: USB CLI, RP<->PIC link, pulser, gain, PIC ICSP programmer.
//
// What it does
//   * USB-C CDC console (115200 8N1 virtual, any baud) with a tiny command line.
//   * UART0 (GPIO16 TX / GPIO17 RX) <-> PIC32AK UART1 at 115200 8N1: "PING n\n" -> "PONG n\n".
//   * TRIG (GPIO6, out), RDY (GPIO7, in) GPIO handshake lines.
//   * PIC MCLR tap on GPIO24: Hi-Z by default, "reset" pulses it low (see note on R53).
//   * PIC PGC1/PGD1 taps on GPIO21/22: kept Hi-Z (inputs, no pulls) so a PICkit on J1 works.
//   * RGB status LED (U5 + LED1 in parallel on GPIO10): blue = no PIC, green = link ok, red = bad reply.
//
// Commands (type on the USB console):
//   help | version | rgb R G B [pct] | reboot [dfu] | ping | auto | stop | reset | rdy | trig | raw <text> | stat
//   pic id | pic image | pic flash | pic verify | pic erase     (ICSP programmer on GPIO21/22/24)
//   link [uart|spi [MHz]] | linktest [count [MHz]] | dac ...    (proto 11: capture payload over SPI0, UART fallback)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/regs/pads_bank0.h"
#include "hardware/address_mapped.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "ws2812.pio.h"
#include "pulser.pio.h"
#include "hardware/clocks.h"
#include "pico/unique_id.h"
#include "pico/bootrom.h"
#include "pico/version.h"
#include "hardware/structs/sysinfo.h"
#include "version.h"
#include "pic_icsp.h"
#include "pic_image.h"
#include "acq_parse.h"
#include "link_frame.h"
#include "hardware/spi.h"

#define LINK_UART      uart0
#define LINK_BAUD      115200
#define LINK_TIMEOUT_US 200000   // 200 ms for a one-line reply (PIC answers within ~1 ms)
#define LINK_IDLE_US    2000     // link_flush_rx: drain until the PIC has been silent this long (was 50 ms while the PIC pushed
                                 // 0.7 s payloads unasked; since proto 11 it only streams on UTX, 23 characters per 2 ms)
#define LINK_DRAIN_MAX_US 2000000 // ... but never longer than this (a PIC that never goes quiet must not hang the CLI)

static uint32_t stat_sent, stat_ok, stat_bad, stat_timeout;
static bool auto_ping = false;
static bool manual_led = false;   // set by "rgb": link status no longer drives the LED
static PIO led_pio; static uint led_sm;

// ---------------------------------------------------------------- RGB status LED
static void led_init(void) {
    led_pio = pio0; led_sm = 0;
    uint off = pio_add_program(led_pio, &ws2812_program);
    ws2812_program_init(led_pio, led_sm, off, MINUS_PIN_RGB, 800000.f);
}
static void led_set(uint8_t r, uint8_t g, uint8_t b);
static void led_status(uint8_t r, uint8_t g, uint8_t b) { if (!manual_led) led_set(r, g, b); }
static void led_rgb(uint8_t r, uint8_t g, uint8_t b) { led_set(r, g, b); }
static void led_set(uint8_t r, uint8_t g, uint8_t b) {
    // GRB order, left-aligned in the 32-bit FIFO word (out shift = 24 bits, MSB first)
    uint32_t grb = ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;
    pio_sm_put_blocking(led_pio, led_sm, grb << 8);
}

// ---------------------------------------------------------------- pulser (board 3: U3 + Q1/Q2 on GPIO8/9, pulser.pio)
// Idle = GPIO8 low (Q2 off), GPIO9 high (Q1 off). The RP2350 pad default (pull-down) on GPIO9 turns Q1 ON, so
// this runs first in main(): until then the "Transducer" net sits at +5 V (see TODO_HARDWARE: pull-up on GPIO9).
#define PULSE_HI_NS   200u
#define PULSE_LO_NS   500u
#define PULSE_DEAD_NS 27u      // both FETs off between +5 V and GND (4 PIO cycles minimum = 26.7 ns at 150 MHz)
static PIO pulse_pio = pio1; static uint pulse_sm = 0, pulse_off = 0;
static void pulser_init(void) {
    pulse_off = pio_add_program(pulse_pio, &pulser_program);
    pulser_program_init(pulse_pio, pulse_sm, pulse_off, MINUS_PIN_PWM_H, MINUS_PIN_RDY);
}
// ns -> PIO cycles at clk_sys, rounded, never below the phase minimum
static unsigned ns_to_cyc(unsigned ns, unsigned min) {
    unsigned c = (unsigned)(((uint64_t)ns * clock_get_hz(clk_sys) + 500000000ull) / 1000000000ull);
    return c < min ? min : c;
}
static double cyc_ns(unsigned c) { return c * 1e9 / (double)clock_get_hz(clk_sys); }
typedef struct { unsigned hi, dead, lo; } pulse_cyc_t;   // actual phase lengths in cycles
static bool pulser_arm(unsigned hi_ns, unsigned lo_ns, unsigned dead_ns, bool now, pulse_cyc_t *pc) {
    unsigned hi = ns_to_cyc(hi_ns, 2), dead = ns_to_cyc(dead_ns, 4), lo = ns_to_cyc(lo_ns, 2);
    if (hi - 2 > 0xFFF || dead - 4 > 0x7F || lo - 2 > 0xFFF) return false;
    pio_sm_clear_fifos(pulse_pio, pulse_sm);
    pio_sm_put(pulse_pio, pulse_sm, (now ? 1u : 0u) | (hi - 2) << 1 | (dead - 4) << 13 | (lo - 2) << 20);
    if (pc) { pc->hi = hi; pc->dead = dead; pc->lo = lo; }
    return true;
}
static bool pulser_fired(void) { return !pio_sm_is_rx_fifo_empty(pulse_pio, pulse_sm); }
// Cancel a shot that never fired (no RDY edge): restart the SM at the program start, pins back to idle.
static void pulser_disarm(void) {
    pio_sm_set_enabled(pulse_pio, pulse_sm, false);
    pio_sm_clear_fifos(pulse_pio, pulse_sm);
    pio_sm_restart(pulse_pio, pulse_sm);
    pio_sm_exec(pulse_pio, pulse_sm, pio_encode_set(pio_pins, 2));
    pio_sm_exec(pulse_pio, pulse_sm, pio_encode_jmp(pulse_off));   // back to "pull block"
    pio_sm_set_enabled(pulse_pio, pulse_sm, true);
}
static void pulse_print(const pulse_cyc_t *pc) {
    printf("pulse: +5V %.1f ns, off %.1f ns, GND %.1f ns, then released (clk_sys %lu MHz)\n",
           cyc_ns(pc->hi), cyc_ns(pc->dead), cyc_ns(pc->lo), (unsigned long)(clock_get_hz(clk_sys) / 1000000));
}
static bool pulse_args(const char *arg, unsigned *hi, unsigned *lo, unsigned *dead, int *in) {
    *hi = PULSE_HI_NS; *lo = PULSE_LO_NS; *dead = PULSE_DEAD_NS;
    if (arg && *arg) { char *e; *hi = (unsigned)strtoul(arg, &e, 10);
        if (*e == ' ') { *lo = (unsigned)strtoul(e + 1, &e, 10);
            if (*e == ' ' && in) { *in = (int)strtol(e + 1, &e, 10); if (*e == ' ') *dead = (unsigned)strtoul(e + 1, NULL, 10); }
            else if (*e == ' ') *dead = (unsigned)strtoul(e + 1, NULL, 10); } }
    return *hi >= 1 && *hi <= 20000 && *lo >= 1 && *lo <= 20000 && *dead <= 800;
}
static void cmd_pulse(const char *arg) {
    // pulse [hi_ns [lo_ns [dead_ns]]]: one shot now, no capture (scope check on H5 / RF1 / RF3)
    unsigned hi, lo, dead; pulse_cyc_t pc;
    if (!pulse_args(arg, &hi, &lo, &dead, NULL) || !pulser_arm(hi, lo, dead, true, &pc)) { printf("usage: pulse [hi_ns [lo_ns [dead_ns]]]  (1..20000, dead <= 800)\n"); return; }
    busy_wait_us(50);
    pulse_print(&pc);
    printf("%s\n", pulser_fired() ? "fired" : "did NOT fire");
    pulser_disarm();
}

// ---------------------------------------------------------------- RX gain (board 3)
// Two non-inverting stages, OA1 and OA2 on the PIC, Rg = 1 k (R28 / R30, AC-coupled by C43 / C44). Rf picked by the
// SN74HC4052 U1, both sections on the same selects (S0 = GPIO25, S1 = GPIO23): leg 0 = 2.2 k (R1 / R26), 1 = 4.7 k
// (R2 / R25), 2 = 6.8 k (R3 / R24), 3 = 10 k (R35 / R36). Per-stage gain 1 + Rf/1k (the mux Ron of ~70 ohm is ignored).
// AMPxCON1.UGE = 1 on the PIC (link "UGE a1 a2") shorts OUT to IN- inside the op amp -> that stage is x1.
static const unsigned gain_rf[4] = { 2200, 4700, 6800, 10000 };
static unsigned gain_leg = 0, gain_u1 = 0, gain_u2 = 0;
static void gain_pins_init(void) {
    gpio_init(MINUS_PIN_GC1); gpio_put(MINUS_PIN_GC1, 0); gpio_set_dir(MINUS_PIN_GC1, GPIO_OUT);
    gpio_init(MINUS_PIN_GC2); gpio_put(MINUS_PIN_GC2, 0); gpio_set_dir(MINUS_PIN_GC2, GPIO_OUT);
}
static double gain_stage(unsigned unity) { return unity ? 1.0 : 1.0 + gain_rf[gain_leg] / 1000.0; }
static double gain_total(void) { return gain_stage(gain_u1) * gain_stage(gain_u2); }
static void gain_desc(char *buf, unsigned n) {
    double g = gain_total();
    snprintf(buf, n, "gain leg %u (Rf %.1fk) OA1 x%.2f%s OA2 x%.2f%s = x%.1f (%.1f dB, + LNA)", gain_leg, gain_rf[gain_leg] / 1000.0,
             gain_stage(gain_u1), gain_u1 ? " (UGE)" : "", gain_stage(gain_u2), gain_u2 ? " (UGE)" : "", g, 20.0 * log10(g));
}

// ---------------------------------------------------------------- link UART helpers
static void link_init(void) {
    uart_init(LINK_UART, LINK_BAUD);
    gpio_set_function(MINUS_PIN_UART_TX, GPIO_FUNC_UART);
    gpio_set_function(MINUS_PIN_UART_RX, GPIO_FUNC_UART);
    uart_set_format(LINK_UART, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(LINK_UART, true);
}
// Drain the link until it has been idle for LINK_IDLE_US: a timed-out `acq` leaves the PIC still
// clocking out its payload (up to ~0.7 s), and this keeps that from poisoning the next command.
// Bounded by LINK_DRAIN_MAX_US: if the PIC chatters continuously (reset loop, wrong baud, floating
// RX) we give up and report it rather than trap every command. Returns false in that case.
static bool link_flush_rx(void) {
    absolute_time_t idle = make_timeout_time_us(LINK_IDLE_US), cap = make_timeout_time_us(LINK_DRAIN_MAX_US);
    while (!time_reached(idle)) {
        if (time_reached(cap)) { printf("link: PIC never idle for %d ms (chatter?), continuing anyway\n", LINK_IDLE_US / 1000); return false; }
        if (uart_is_readable(LINK_UART)) { (void)uart_getc(LINK_UART); idle = make_timeout_time_us(LINK_IDLE_US); }
    }
    return true;
}
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

// ---------------------------------------------------------------- SPI data link (proto 11)
// The PIC no longer pushes capture payloads after the ACQ header: the RP pulls them, by default as one SPI frame
// ("SPIX": PIC = SPI1 client, RP = SPI0 master on GPIO2 SCK / GPIO4 MISO / GPIO3 MOSI unused, GPIO5 = CS), with the
// old UART byte stream ("UTX") as fallback and reference. Frame + checks: link_frame.h. PIC client max SCK = 25 MHz.
// Design: docs/claude/specs/2026-11-21-dac-spi-link-design.md
#define LINK_SPI        spi0
#define LINK_SPI_HZ_DEF 12500000u    // 150 MHz / 12 exactly; linktest decides how far up it can go (<= 25 MHz)
#define LINK_UTX_US     2000000u     // UART fallback: 8190 B at 115200 baud ~ 0.71 s
static bool     link_use_spi = true;
static unsigned link_spi_hz;
static uint32_t lk_frames, lk_frame_err, lk_fallback, lk_noreply;
static int64_t  lk_last_us = -1;
static unsigned lk_last_bytes;
static uint8_t  link_buf[LINK_FRAME_LEN(LINK_MAX_N)];

static void link_spi_init(void) {
    link_spi_hz = spi_init(LINK_SPI, LINK_SPI_HZ_DEF);
    spi_set_format(LINK_SPI, 8, SPI_CPOL_0, SPI_CPHA_1, SPI_MSB_FIRST);   // mode 1: no inter-byte gap (mode 0 on the PL022 costs ~19 %)
    gpio_set_function(MINUS_PIN_SPI_SCK, GPIO_FUNC_SPI);
    gpio_set_function(MINUS_PIN_SPI_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(MINUS_PIN_SPI_MISO, GPIO_FUNC_SPI);
    gpio_init(MINUS_PIN_SPI_CS); gpio_put(MINUS_PIN_SPI_CS, 1); gpio_set_dir(MINUS_PIN_SPI_CS, GPIO_OUT);
}

// Ask for the pending payload as an SPI frame (proto 12): "SPIX" on the UART, the PIC preloads its FIFO and raises RDY,
// the RP clocks the frame with CS low; no reply line. 0 = ok (*payload points into link_buf), -1 = failed (why filled in).
static int64_t lk_last_ready_us = -1, lk_last_wire_us = -1;
static int link_spi_fetch(unsigned want_n, const uint8_t **payload, int64_t *us, char *why, unsigned whylen) {
    absolute_time_t t0 = get_absolute_time();
    link_puts("SPIX\n");
    uart_tx_wait_blocking(LINK_UART);                    // the '\n' has left: the PIC parses SPIX within a few us
    busy_wait_us(20);                                    // past its RDY drop (RDY may be high from an old PING toggle)
    absolute_time_t dl = make_timeout_time_us(5000);
    while (!gpio_get(MINUS_PIN_RDY) && !time_reached(dl)) {
        if (uart_is_readable(LINK_UART)) break;          // "SPIX 0" = nothing pending
    }
    if (!gpio_get(MINUS_PIN_RDY)) {
        char rx[48] = "";
        int r = link_readline(rx, sizeof rx, 2000);
        lk_noreply++; snprintf(why, whylen, r >= 0 ? "PIC said '%.30s'" : "no RDY from the PIC", rx);
        return -1;
    }
    absolute_time_t t1 = get_absolute_time();
    unsigned len = LINK_FRAME_LEN(want_n);
    gpio_put(MINUS_PIN_SPI_CS, 0);
    busy_wait_us(1);                                     // SS1 set-up on the PIC side
    spi_read_blocking(LINK_SPI, 0x00, link_buf, len);
    gpio_put(MINUS_PIN_SPI_CS, 1);
    absolute_time_t t2 = get_absolute_time();
    link_frame_t fr;
    link_err_t e = link_frame_check(link_buf, len, want_n, LINK_ANY_SEQ, &fr);
    *us = absolute_time_diff_us(t0, t2);
    lk_last_ready_us = absolute_time_diff_us(t0, t1); lk_last_wire_us = absolute_time_diff_us(t1, t2);
    if (e != LINK_OK) { lk_frame_err++; snprintf(why, whylen, "frame %s", link_err_name(e)); return -1; }
    lk_frames++; lk_last_us = *us; lk_last_bytes = len;
    *payload = fr.payload;
    return 0;
}

// The same payload over the UART into dst (2n bytes). 0 = ok, -1 = failed.
static int link_uart_fetch(unsigned want_n, uint8_t *dst, int64_t *us, char *why, unsigned whylen) {
    char rx[48]; unsigned n;
    absolute_time_t t0 = get_absolute_time();
    link_puts("UTX\n");
    if (link_readline(rx, sizeof rx, 500000) < 0) { snprintf(why, whylen, "no UTX reply"); return -1; }
    if (sscanf(rx, "UTX %u", &n) != 1 || n != want_n) { snprintf(why, whylen, "UTX reply '%.30s'", rx); return -1; }
    unsigned want = 2 * n, got = 0;
    absolute_time_t deadline = make_timeout_time_us(LINK_UTX_US);
    while (got < want && !time_reached(deadline))
        if (uart_is_readable(LINK_UART)) dst[got++] = (uint8_t)uart_getc(LINK_UART);
    *us = absolute_time_diff_us(t0, get_absolute_time());
    if (got < want) { snprintf(why, whylen, "short UART payload %u of %u B", got, want); return -1; }
    return 0;
}

// Pending payload of n samples: SPI (if enabled), else / on failure UART. NULL = nothing received.
static const uint8_t *link_fetch(unsigned n, char *info, unsigned infolen) {
    char why[80] = "", why2[80] = ""; int64_t us = -1; const uint8_t *p = NULL;
    if (link_use_spi) {
        if (link_spi_fetch(n, &p, &us, why, sizeof why) == 0) {
            snprintf(info, infolen, "link=spi@%.2fMHz xfer=%lldus", link_spi_hz / 1e6, (long long)us);
            return p;
        }
        lk_fallback++;
        link_flush_rx();                                 // the PIC may still be finishing its frame
    }
    if (link_uart_fetch(n, link_buf + 8, &us, why2, sizeof why2) == 0) {
        if (link_use_spi) snprintf(info, infolen, "link=uart(spi failed: %s) xfer=%lldus", why, (long long)us);
        else snprintf(info, infolen, "link=uart xfer=%lldus", (long long)us);
        return link_buf + 8;
    }
    printf("acq: payload not received (%s%s%s)\n", why, *why ? "; " : "", why2);
    return NULL;
}

// ---------------------------------------------------------------- sample output + time-gain schedule (rp 1.1.7, proto 14)
// fmt b64: the samples go out as "# b64 <bytes>" + base64 lines (76 chars = 57 bytes, u16 little-endian) instead of one decimal
// per line: ~11 KB instead of ~24.8 KB per 4095-sample capture, the USB CDC (256-byte sdk buffer, ~270 kB/s) being the limit.
static bool out_b64 = false;
static void print_samples(const uint8_t *p, unsigned n) {
    static char tbuf[4096]; unsigned tl = 0;
    if (!out_b64) {
        for (unsigned i = 0; i < n; i++) {
            tl += (unsigned)snprintf(tbuf + tl, sizeof tbuf - tl, "%u\n", (unsigned)p[2 * i] | (unsigned)p[2 * i + 1] << 8);
            if (tl > sizeof tbuf - 16) { fwrite(tbuf, 1, tl, stdout); tl = 0; }
        }
    } else {
        unsigned nb = 2 * n;
        printf("# b64 %u\n", nb);
        for (unsigned i = 0; i < nb; i += 57) {
            unsigned k = nb - i < 57 ? nb - i : 57;
            tl += link_b64_encode(p + i, k, tbuf + tl);
            tbuf[tl++] = '\n';
            if (tl > sizeof tbuf - 80) { fwrite(tbuf, 1, tl, stdout); tl = 0; }
        }
    }
    if (tl) fwrite(tbuf, 1, tl, stdout);
    fflush(stdout);
}
static void cmd_fmt(const char *arg) {
    if (arg && *arg) {
        if (!strcmp(arg, "text")) out_b64 = false;
        else if (!strcmp(arg, "b64")) out_b64 = true;
        else { printf("usage: fmt [text|b64]\n"); return; }
    }
    printf("fmt: %s\n", out_b64 ? "b64 (samples as '# b64 <bytes>' + base64 lines of u16 little-endian)" : "text (one decimal sample per line)");
}

// tgc: switch the 74HC4052 gain leg (both stages, S0 = GPIO25, S1 = GPIO23) at set times after the capture start (= the pulse,
// RDY rise) — time-gain compensation by steps. Applied by acq/pe/acqos/acqcpu/acqil (acq_receive) and tof/env; the leg set by
// "gain" is restored at the end of each capture. UGE (x1 per stage) is not touched.
#define TGC_MAX 4
static unsigned tgc_n, tgc_t_us[TGC_MAX], tgc_leg[TGC_MAX];
static void tgc_set_leg(unsigned leg) { gpio_put(MINUS_PIN_GC1, leg & 1u); gpio_put(MINUS_PIN_GC2, (leg >> 1) & 1u); }
static unsigned gain_leg_cur(void);
// RDY rose at t0: run the schedule while RDY is high (<= 20 ms), restore the gain leg; returns the RDY-high time in us
static int64_t rdy_window(absolute_time_t t0) {
    unsigned k = 0; absolute_time_t t_end = delayed_by_ms(t0, 20);
    while (gpio_get(MINUS_PIN_RDY) && !time_reached(t_end)) {
        if (k < tgc_n && absolute_time_diff_us(t0, get_absolute_time()) >= (int64_t)tgc_t_us[k]) { tgc_set_leg(tgc_leg[k]); k++; }
    }
    int64_t d = absolute_time_diff_us(t0, get_absolute_time());
    if (tgc_n) tgc_set_leg(gain_leg_cur());
    return d;
}
static void tgc_desc(char *buf, unsigned len) {
    unsigned o = 0; buf[0] = 0;
    if (!tgc_n) return;
    o += (unsigned)snprintf(buf + o, len - o, " tgc=");
    for (unsigned k = 0; k < tgc_n && o < len; k++) o += (unsigned)snprintf(buf + o, len - o, "%s%uus:leg%u", k ? "," : "", tgc_t_us[k], tgc_leg[k]);
}
// tgc [off | <t_us> <leg> [<t_us> <leg> ...]]: up to 4 steps, times increasing, 0..20000 us, legs 0..3
static void cmd_tgc(const char *arg) {
    if (arg && *arg) {
        if (!strcmp(arg, "off")) tgc_n = 0;
        else {
            unsigned t[TGC_MAX], l[TGC_MAX], n = 0; const char *q = arg; int used;
            while (n < TGC_MAX && sscanf(q, "%u %u%n", &t[n], &l[n], &used) == 2) { q += used; n++; while (*q == ' ') q++; }
            bool ok = n > 0 && *q == 0;
            for (unsigned k = 0; k < n && ok; k++) ok = l[k] <= 3 && t[k] <= 20000 && (k == 0 || t[k] > t[k - 1]);
            if (!ok) { printf("usage: tgc [off | <t_us> <leg> [<t_us> <leg> ...]]  up to 4 steps, times increasing (0..20000 us after the pulse), legs 0..3\n"); return; }
            for (unsigned k = 0; k < n; k++) { tgc_t_us[k] = t[k]; tgc_leg[k] = l[k]; }
            tgc_n = n;
        }
    }
    char d[96]; tgc_desc(d, sizeof d);
    printf("tgc: %s (leg %u from gain before the first step and after the capture)\n", tgc_n ? d + 5 : "off", gain_leg_cur());
}

// ---------------------------------------------------------------- PIC control taps
static void pic_taps_init(void) {
    // The RP's own SWCLK/SWDIO pads sit on PGD1/PGC1 (R17/R18 0R + R8/R10 47R to J1.4/J1.5) and
    // default to pull-ups (PADS_BANK0 SWCLK/SWD PUE=1): they would make the ICSP lines read HIGH
    // even with no PIC at all (seen 2026-10-27). Disable those pulls so `pic pins` and reads are honest.
    hw_clear_bits((io_rw_32 *)(PADS_BANK0_BASE + PADS_BANK0_SWCLK_OFFSET), PADS_BANK0_SWCLK_PUE_BITS | PADS_BANK0_SWCLK_PDE_BITS);
    hw_clear_bits((io_rw_32 *)(PADS_BANK0_BASE + PADS_BANK0_SWD_OFFSET),   PADS_BANK0_SWD_PUE_BITS   | PADS_BANK0_SWD_PDE_BITS);
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
    if (n < 0) { stat_timeout++; led_status(0, 0, 40); if (verbose) printf("ping %lu: timeout (%lld us)\n", (unsigned long)seq, dt); return false; }
    if (strcmp(rx, want) == 0) { stat_ok++; led_status(0, 40, 0); if (verbose) printf("ping %lu: ok, %lld us, rdy=%d\n", (unsigned long)seq, dt, gpio_get(MINUS_PIN_RDY)); return true; }
    stat_bad++; led_status(40, 0, 0);
    if (verbose) printf("ping %lu: bad reply '%s' (%lld us)\n", (unsigned long)seq, rx, dt);
    return false;
}

// ---------------------------------------------------------------- I2C0 (GPIO0 SDA / GPIO1 SCL, 10k pull-ups R41/R42)
// Shared bus, RP is the only master: MCP4531 U11 (0x2E, A0 = GND) = OA2 feedback rheostat, MCP4531 U18 (0x2F,
// A0 = AVDD) -> JP6/JP7 toward the AD8338 VGA, MCP4728 U13 (0x60) DAC, OLED1 (0x3C). The PIC's ASDA2/ASCL2 sit on
// the same pins and stay Hi-Z.
static bool i2c_ready = false;
static void i2c_ensure(void) {
    if (i2c_ready) return;
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(MINUS_PIN_SDA, GPIO_FUNC_I2C); gpio_set_function(MINUS_PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(MINUS_PIN_SDA); gpio_pull_up(MINUS_PIN_SCL);
    i2c_ready = true;
}
static const char *i2c_name(unsigned a) {
    return a == 0x2E ? "MCP4531 U11 (OA2 feedback rheostat)" : a == 0x2F ? "MCP4531 U18 (AD8338 gain, via JP6/JP7)" :
           a == 0x60 ? "MCP4728 U13 (DAC)" : a == 0x3C ? "OLED1" : a == 0x30 ? "LP5562 U5 (RGB LED driver)" : "?";
}
static void cmd_i2c(void) {
    // i2c: scan 0x08..0x77 with a zero-length write (ACK = device present)
    i2c_ensure(); int found = 0;
    for (unsigned a = 0x08; a < 0x78; a++) {
        uint8_t d; int r = i2c_read_timeout_us(i2c0, (uint8_t)a, &d, 1, false, 2000);
        if (r >= 0) { printf("  0x%02X  %s\n", a, i2c_name(a)); found++; }
    }
    printf("i2c scan: %d device(s)\n", found);
}
// LP5562 U5 (board 3, I2C 0x30: ADDR_SEL0/1 = GND, EN tied to VCC) -> RGB LED U4 on its R/G/B outputs (W unused).
// Datasheet programming sequence: ENABLE (0x00) = 0x40 chip_en, wait 500 us, CONFIG (0x08) = 0x01 internal clock (so the
// external 32 kHz OSC1 is not needed), LED_MAP (0x70) = 0x00 all channels under I2C control, then the PWM registers
// B 0x02 / G 0x03 / R 0x04 (0..255). Currents stay at the power-on 17.5 mA per channel.
static bool lp5562_ready = false;
static int lp5562_wr(uint8_t reg, uint8_t v) {
    uint8_t tx[2] = { reg, v };
    return i2c_write_timeout_us(i2c0, 0x30, tx, 2, false, 5000) == 2 ? 0 : -1;
}
static int lp5562_rgb(uint8_t r, uint8_t g, uint8_t b) {
    i2c_ensure();
    if (!lp5562_ready) {
        if (lp5562_wr(0x00, 0x40) < 0) return -1;
        sleep_us(500);
        if (lp5562_wr(0x08, 0x01) < 0 || lp5562_wr(0x70, 0x00) < 0) return -1;
        lp5562_ready = true;
    }
    if (lp5562_wr(0x04, r) < 0 || lp5562_wr(0x03, g) < 0 || lp5562_wr(0x02, b) < 0) { lp5562_ready = false; return -1; }
    return 0;
}
// MCP4531 (7-bit, 129 taps, volatile wiper 0): write = [addr W] [0x00 | D8] [D7..0]; read = [addr W] [0x0C] then
// [addr R] 2 bytes (D8 in bit 0 of the first). RAB 10k typ, RW ~75 ohm: R_AW(n) = RAB x (128 - n) / 128 + RW.
static int mcp4531_read(unsigned a0, unsigned *n) {
    i2c_ensure(); uint8_t cmd = 0x0C, rx[2];
    if (i2c_write_timeout_us(i2c0, 0x2E + a0, &cmd, 1, true, 5000) != 1) return -1;
    if (i2c_read_timeout_us(i2c0, 0x2E + a0, rx, 2, false, 5000) != 2) return -1;
    *n = ((rx[0] & 1u) << 8) | rx[1]; return 0;
}
static int mcp4531_write(unsigned a0, unsigned n) {
    i2c_ensure(); uint8_t tx[2] = { (uint8_t)((n >> 8) & 1u), (uint8_t)(n & 0xFF) };
    return i2c_write_timeout_us(i2c0, 0x2E + a0, tx, 2, false, 5000) == 2 ? 0 : -1;
}
static void cmd_pot(const char *arg) {
    // pot <0|1> [n]: read (or set to n = 0..128, then read back) the MCP4531 wiper; 0 = U11 = OA2 feedback.
    unsigned a0 = 0, n = 0; int set = 0;
    if (arg && *arg) { char *e; a0 = (unsigned)strtoul(arg, &e, 10); if (*e == ' ') { n = (unsigned)strtoul(e + 1, NULL, 10); set = 1; } }
    if (a0 > 1 || n > 128) { printf("usage: pot <0|1> [n 0..128]   (0 = U11 OA2 feedback, 1 = U18 AD8338 gain)\n"); return; }
    if (set && mcp4531_write(a0, n) < 0) { printf("pot %u: write NAK\n", a0); return; }
    unsigned got; if (mcp4531_read(a0, &got) < 0) { printf("pot %u: read NAK (no device at 0x%02X?)\n", a0, 0x2E + a0); return; }
    double raw = 10000.0 * (128.0 - (double)got) / 128.0 + 75.0;
    if (a0 == 0) printf("pot 0 (U11, 0x2E): wiper %u -> R_AW ~ %.0f ohm -> OA2 gain = 1 + R_AW / R49 1k ~ x%.2f%s\n", got, raw, 1.0 + raw / 1000.0, set ? " (set)" : "");
    else printf("pot 1 (U18, 0x2F): wiper %u -> R_AW ~ %.0f ohm%s\n", got, raw, set ? " (set)" : "");
}
static void cmd_version(void) {
    char uid[2 * PICO_UNIQUE_BOARD_ID_SIZE_BYTES + 1];
    pico_get_unique_board_id_string(uid, sizeof uid);
    printf("%s %s proto %d (built " __DATE__ " " __TIME__ ", pico-sdk " PICO_SDK_VERSION_STRING ")\n", FW_NAME, FW_VERSION, PROTO_VERSION);
    printf("board: minus v1.1, flash %u kB\n", PICO_FLASH_SIZE_BYTES / 1024);
    printf("chip: RP2354A  chip_id=0x%08lx package_sel=0x%lx version=A%u\n",
           (unsigned long)sysinfo_hw->chip_id, (unsigned long)sysinfo_hw->package_sel, rp2350_chip_version());
    printf("unique id: %s\n", uid);
}

static void cmd_reboot(const char *arg) {
    if (arg && !strcmp(arg, "dfu")) {
        printf("rebooting into BOOTSEL (UF2 drive)...\n"); sleep_ms(50);
        rom_reset_usb_boot(0, 0);            // same as holding BOOTSEL: RP2350 USB mass-storage/PICOBOOT
    }
    printf("rebooting...\n"); sleep_ms(50);
    // watchdog-free reboot via the ROM: AIRCR SYSRESETREQ
    *(volatile uint32_t *)0xE000ED0C = (0x5FAUL << 16) | (1u << 2);
    while (true) tight_loop_contents();
}

// ---------------------------------------------------------------- PIC32 ICSP programmer
static bool pic_verify_image(unsigned *bad_words) {
    uint32_t buf[64]; unsigned bad = 0, first_bad = 0; bool any = false;
    for (const pic_segment_t *sg = pic_image_segments; sg->len; sg++) {
        for (uint32_t off = 0; off < sg->len; off += sizeof buf) {
            unsigned n = (sg->len - off) / 4; if (n > 64) n = 64;
            pic_read_block(sg->addr + off, buf, n);
            for (unsigned i = 0; i < n; i++) {
                const uint8_t *p = sg->data + off + 4 * i;
                uint32_t want = (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
                if (buf[i] != want) { if (!any) { any = true; first_bad = sg->addr + off + 4 * i;
                        printf("  mismatch @0x%06lx: read 0x%08lx want 0x%08lx\n", (unsigned long)first_bad, (unsigned long)buf[i], (unsigned long)want); }
                    bad++; }
            }
        }
    }
    if (bad_words) *bad_words = bad;
    return bad == 0;
}

static void cmd_pic(const char *arg) {
    if (!arg || !*arg || !strcmp(arg, "help")) {
        printf("pic pins    read PGC/PGD/MCLR/RDY/UART_RX levels (who drives what)\n"
               "pic mclr low|hiz   hold the MCLR tap low for a meter check / release it\n"
               "pic mclr rise      measure the MCLR node rise time after release (< 5 us = C31 really off)\n"
               "pic slow|fast      ICSP clock ~100 kHz / ~1.2 MHz (diagnostic; default fast)\n"
               "pic rdraw [addr [idle [nbits [ncmd]]]]  diagnostic: raw CMDSEQRD bit streams (defaults DEVID 1 33 4)\n"
               "pic seq <ops> [addr]   diagnostic: S=CMDSEQRD R=CMDRD N=NOP-exec W=MOV.L[W9],[W8] E<hex8>=exec; prints read windows\n"
               "pic pair 1|2       ICSP pins: 1 = PGC1/PGD1 (GPIO21/22); 2 = PGC2/PGD2 (jumper H2.16 -> CN1.17, PGD2 = TRIG/GPIO6)\n"
               "pic id      enter ICSP, read DEVID/REVID, exit (no write)\n"
               "pic image   describe the PIC image embedded in this firmware\n"
               "pic flash   bulk erase + program + verify the embedded image, then run the PIC\n"
               "pic verify  compare PIC flash with the embedded image (no write)\n"
               "pic erase   bulk erase only (PIC is blank afterwards)\n"
               "needs: R53 = 0R, JP1 cut (C31 off MCLR), nothing plugged on J1\n");
        return;
    }
    if (!strcmp(arg, "pins")) {
        // read every PIC-side line as a plain input (no pulls): tells us what the board holds them at
        const struct { const char *n; uint pin; } L[] = {{"PGC1/GPIO21", MINUS_PIN_PIC_PGC}, {"PGD1/GPIO22", MINUS_PIN_PIC_PGD},
            {"MCLR/GPIO24", MINUS_PIN_PIC_MCLR}, {"RDY/GPIO7", MINUS_PIN_RDY}, {"UART_RX/GPIO17", MINUS_PIN_UART_RX}};
        for (unsigned i = 0; i < sizeof L / sizeof L[0]; i++) {
            bool was_out = gpio_get_dir(L[i].pin) == GPIO_OUT; uint fn = gpio_get_function(L[i].pin);
            gpio_set_function(L[i].pin, GPIO_FUNC_SIO); gpio_set_dir(L[i].pin, GPIO_IN); gpio_disable_pulls(L[i].pin);
            busy_wait_us(50); int v = gpio_get(L[i].pin);
            gpio_set_pulls(L[i].pin, true, false); busy_wait_us(50); int vu = gpio_get(L[i].pin);
            gpio_set_pulls(L[i].pin, false, true); busy_wait_us(50); int vd = gpio_get(L[i].pin);
            gpio_disable_pulls(L[i].pin);
            printf("  %-15s level=%d  with pull-up=%d  with pull-down=%d  -> %s\n", L[i].n, v, vu, vd,
                   (vu == vd) ? (vu ? "driven HIGH externally" : "driven LOW externally") : "floating (nothing drives it)");
            if (was_out) gpio_set_dir(L[i].pin, GPIO_OUT);
            gpio_set_function(L[i].pin, fn);
        }
        printf("note: RP SWD pad pulls are OFF (fw >= 0.1.6); a blank PIC leaves PGC1/PGD1 floating. MCLR must be HIGH via R5.\n");
        return;
    }
    if (!strncmp(arg, "mclr", 4)) {
        const char *m = arg[4] == ' ' ? arg + 5 : "";
        if (!strcmp(m, "low")) {
            gpio_init(MINUS_PIN_PIC_MCLR); gpio_put(MINUS_PIN_PIC_MCLR, 0); gpio_set_dir(MINUS_PIN_PIC_MCLR, GPIO_OUT);
            printf("GPIO24 driving LOW. Measure J1 pin 1 (PIC MCLR): must be < 0.66 V (stock R53 4k7 gives ~1.05 V). 'pic mclr hiz' to release.\n");
        } else if (!strcmp(m, "hiz")) {
            gpio_set_dir(MINUS_PIN_PIC_MCLR, GPIO_IN); gpio_disable_pulls(MINUS_PIN_PIC_MCLR); printf("GPIO24 released (Hi-Z)\n");
        } else if (!strcmp(m, "rise")) {
            uint32_t us = icsp_mclr_rise_us();
            printf("MCLR rise after release: %lu us -> %s\n", (unsigned long)us,
                   us < 20 ? "C31 is off the node (JP1 cut OK)" : us < 50000 ? "slow: C31 (470 nF) still on the node?" : "never rose: no pull-up / shorted low?");
        } else printf("usage: pic mclr low | hiz | rise\n");
        return;
    }
    if (!strncmp(arg, "seq ", 4)) {
        // pic seq <ops> [addr]   e.g. pic seq SRRR  /  pic seq SNS 0x7C2000
        char ops[32] = {0}; uint32_t a = 0x7C2000u; const char *e = arg + 4; unsigned k = 0;
        while (*e && *e != ' ' && k < sizeof ops - 1) ops[k++] = *e++;
        if (*e == ' ') a = strtoul(e + 1, NULL, 0);
        static char raw[1200];
        icsp_enter(); pic_seq_raw(a, ops, raw, sizeof raw); icsp_exit();
        printf("seq %s @0x%06lx (window = idle bit '.' 32 data LSB-first '.' trailing):\n%s\n", ops, (unsigned long)a, raw);
        return;
    }
    if (!strncmp(arg, "rdraw", 5)) {
        uint32_t a = 0x7C2000u; unsigned idle = 1, nbits = 33, ncmd = 4; char *e = (char *)arg + 5;
        if (*e == ' ') { a = strtoul(e, &e, 0); if (*e == ' ') { idle = strtoul(e, &e, 0); if (*e == ' ') { nbits = strtoul(e, &e, 0); if (*e == ' ') ncmd = strtoul(e, &e, 0); } } }
        if (nbits > 96) nbits = 96; if (ncmd > 6) ncmd = 6;
        static char raw[6 * 110];
        icsp_enter(); pic_read_raw(a, ncmd, idle, nbits, raw, sizeof raw); icsp_exit();
        printf("raw CMDSEQRD @0x%06lx idle=%u nbits=%u: '|' = after the 11 command, i/I = idle clock level, then sampled bits LSB first ('.' after bit 31); PGD pull-down while listening\n%s\n", (unsigned long)a, idle, nbits, raw);
        return;
    }
    if (!strncmp(arg, "pair", 4)) { if (arg[4] == ' ') icsp_set_pair(arg[5] - '0'); printf("ICSP pair %d: PGC on GPIO21, PGD on GPIO%d%s\n", icsp_get_pair(), icsp_get_pair() == 2 ? MINUS_PIN_TRIG : MINUS_PIN_PIC_PGD, icsp_get_pair() == 2 ? " (TRIG line = PIC RA0/PGD2; jumper H2.16 (RA1/PGC2) to CN1.17)" : ""); return; }
    if (!strcmp(arg, "slow") || !strcmp(arg, "fast")) { icsp_set_slow(arg[0] == 's'); printf("ICSP clock: %s\n", icsp_get_slow() ? "slow (~100 kHz)" : "fast (~1.2 MHz)"); return; }
    if (!strcmp(arg, "image")) {
        printf("image '%s': %u segment(s), %u bytes\n", pic_image_name, pic_image_nseg, pic_image_bytes);
        for (const pic_segment_t *sg = pic_image_segments; sg->len; sg++)
            printf("  0x%06lx +%lu %s\n", (unsigned long)sg->addr, (unsigned long)sg->len,
                   sg->addr >= 0x800000u ? "code" : "config (UCA/UCB)");
        return;
    }
    bool want_flash = !strcmp(arg, "flash"), want_verify = !strcmp(arg, "verify"), want_erase = !strcmp(arg, "erase"), want_id = !strcmp(arg, "id");
    if (!(want_flash || want_verify || want_erase || want_id)) { printf("pic: unknown '%s' (pic help)\n", arg); return; }
    if ((want_flash || want_verify) && pic_image_nseg == 0) { printf("no PIC image embedded (build with firmware/pic32/build/minus_pic.hex present)\n"); return; }

    uint32_t devid = 0, revid = 0;
    icsp_enter();
    bool ok = pic_read_id(&devid, &revid);
    printf("ICSP pair %d %s, %lu PGC clocks. ", icsp_get_pair(), icsp_get_slow() ? "slow" : "fast", (unsigned long)icsp_clocks());
    printf("DEVID 0x%04lx DEVREV %lu -> %s\n", (unsigned long)(devid & 0xFFFF), (unsigned long)(revid & 0xF),
           ok ? "PIC32AK1216GC41048" : (devid == 0 || devid == 0xFFFFFFFFu ? "no response (check R53=0R, JP1 cut, J1 empty, PIC powered)" : "unexpected device"));
    if (!ok) { icsp_exit(); return; }

    if (want_erase || want_flash) {
        absolute_time_t t0 = get_absolute_time();
        bool e = pic_bulk_erase();
        printf("bulk erase: %s (%lld ms)\n", e ? "ok" : "TIMEOUT", absolute_time_diff_us(t0, get_absolute_time()) / 1000);
        if (!e) { icsp_exit(); return; }
    }
    if (want_flash) {
        absolute_time_t t0 = get_absolute_time(); bool p = true;
        for (const pic_segment_t *sg = pic_image_segments; sg->len && p; sg++) {
            p = pic_program_quadwords(sg->addr, sg->data, sg->len);
            printf("  program 0x%06lx +%lu: %s\n", (unsigned long)sg->addr, (unsigned long)sg->len, p ? "ok" : "TIMEOUT");
        }
        printf("program: %s (%lld ms, %lu PGC clocks)\n", p ? "ok" : "FAILED", absolute_time_diff_us(t0, get_absolute_time()) / 1000, (unsigned long)icsp_clocks());
        if (!p) { icsp_exit(); return; }
    }
    if (want_flash || want_verify) {
        unsigned bad = 0; bool v = pic_verify_image(&bad);
        printf("verify: %s (%u bad words of %u)\n", v ? "ok" : "MISMATCH", bad, pic_image_bytes / 4);
    }
    icsp_exit();
    printf("ICSP exit, PIC released (MCLR Hi-Z)%s\n", want_flash ? " — try 'ping'" : "");
}

// ---------------------------------------------------------------- acq: 4095 ADC samples from the PIC
#define ACQ_MAX_N 4095u
static int acq_receive(char *hdr, unsigned hdrlen, const char *note, unsigned long max_fill_ns);
// Input codes (PIC fw >= 0.1.22): 0..15 = ADC1 PINSEL, 16..31 = ADC2 PINSEL + 16. Names for board 3 (v1.1).
static const char *acq_in_name(int in) {
    switch (in) {
    case 25: return "AD2AN9 (PIC32_ADC: OA2OUT after the R67/C86/R68/C87 filter, board 3)";
    case 17: return "AD2AN1 (OA2OUT, before the filter)";
    case 0:  return "AD1AN0 (OA1OUT)";
    case 1:  return "AD1AN1 (OA1IN+ = LNA output after C40, board 3; raw RX node on the devkit)";
    case 9:  return "AD1AN9 (PIC32_ADC on the devkit; unconnected on board 3)";
    default: return in < 16 ? "ADC1 input" : "ADC2 input";
    }
}
// PIC slow lock (pic >= 1.1.2): a PLL1 lock can leave the ADC in the 40/60/60 ns pattern for good (bench 2026-11-22). The PIC
// re-locks at boot until uniform; if captures still come back slow 3 times in a row, ask it to re-lock now ("RELOCK" re-runs
// its acq_init, so the op-amp unity-gain bits are restored from the RP's gain state afterwards).
static unsigned gain_u1_cur(void);
static unsigned gain_u2_cur(void);
static void pic_relock(void) {
    char rx[48] = "", tx[24];
    link_flush_rx(); link_puts("RELOCK\n");
    int r = link_readline(rx, sizeof rx, 1000000);
    snprintf(tx, sizeof tx, "UGE %u %u\n", gain_u1_cur(), gain_u2_cur());
    link_puts(tx); char rx2[32]; link_readline(rx2, sizeof rx2, LINK_TIMEOUT_US);
    printf("# PIC re-locked its PLL after 3 slow captures: %s\n", r >= 0 ? rx : "no reply");
}

static void cmd_acq(const char *arg) {
    char hdr[96];
    unsigned div = 0; int samc = -2; int in = -1; int navg = 0;            // div 0 = PIC default; samc -2 / in -1 / navg 0 = not given
    if (arg && *arg) {
        char *e; div = (unsigned)strtoul(arg, &e, 10);
        if (*e == ' ') { samc = (int)strtol(e + 1, &e, 10);
            if (*e == ' ') { in = (int)strtol(e + 1, &e, 10); if (*e == ' ') navg = (int)strtol(e + 1, NULL, 10); } }
    }
    if (in > 31) { printf("acq: in must be 0..31 (0..15 ADC1 PINSEL, 16..31 ADC2: 25 = AD2AN9 node, 0 OA1OUT, 1 OA1IN+)\n"); return; }
    if (navg < 0 || navg > 16) { printf("acq: navg must be 1..16\n"); return; }
    link_flush_rx();
    if (div && navg) snprintf(hdr, sizeof hdr, "ACQ %u %d %d %d\n", div, samc == -2 ? 0 : samc, in < 0 ? 25 : in, navg);
    else if (div && in >= 0) snprintf(hdr, sizeof hdr, "ACQ %u %d %d\n", div, samc == -2 ? 0 : samc, in);
    else if (div && samc != -2) snprintf(hdr, sizeof hdr, "ACQ %u %d\n", div, samc);
    else if (div) snprintf(hdr, sizeof hdr, "ACQ %u\n", div);
    else snprintf(hdr, sizeof hdr, "ACQ\n");
    link_puts(hdr);
    // The PIC keeps the last div/samc/in across ACQ calls, so only name the input when this call set it.
    const char *inname = in < 0 ? "last input (AD2AN9 node unless changed)" : acq_in_name(in);
    char note[200];
    snprintf(note, sizeof note, "trigger div %u; in=%d %s; navg=%d (%s)", div ? div : 4, in, inname,
             navg, navg > 1 ? "each value = sum of navg back-to-back 32 ns conversions, 12+log2(navg) bits" : navg == 1 ? "12-bit unsigned" : "unchanged from the last acq");
    // the PIC answers "slow" (no payload) when the ADC locked to the 40/60/60 ns pattern: capture again, up to 8 times
    char cmdline[96]; memcpy(cmdline, hdr, sizeof cmdline);
    int tries = 1, r;
    while ((r = acq_receive(hdr, sizeof hdr, note, 0xFFFFFFFFul)) == 1 && tries < 8) {
        if (tries == 3) pic_relock();
        tries++; link_flush_rx(); memcpy(hdr, cmdline, sizeof cmdline); link_puts(hdr);
    }
    if (r == 1) printf("acq: %d captures, every one had a non-uniform (slow) sample clock — nothing printed (DMA busy elsewhere, e.g. 'dac sine'? try div 10)\n", tries);
}
// pe [hi_ns [lo_ns [in [dead_ns]]]]: pulse-echo. Arms the pulser on the PIC's RDY rising edge (the PIC raises RDY
// one instruction before it starts the SCCP1 ADC trigger), then runs "ACQ 4 0 <in> 1" = 4095 samples at 25 Msps
// (40 ns) on input <in> (default 25 = AD2AN9, the filtered RX node on board 3), single conversions.
static void cmd_pe(const char *arg) {
    unsigned hi, lo, dead; int in = 25; pulse_cyc_t pc; char hdr[96];
    if (!pulse_args(arg, &hi, &lo, &dead, &in) || in < 0 || in > 31) { printf("usage: pe [hi_ns [lo_ns [in [dead_ns]]]]  (defaults 200 500 25 27; in = 0..15 ADC1, 16..31 ADC2)\n"); return; }
    char note[360], g[160]; gain_desc(g, sizeof g);
    // The 32 ns ADC on 20 ns SCCP triggers locks to every 2nd trigger (40 ns) most of the time, but some starts lock to a
    // 40/60/60 ns pattern (53.3 ns mean, echoes at 0.75x the sample index, fill ~226 us instead of 164.7): bench
    // 2026-11-19. Uniform 40 ns = 4095 x 40 = 163.8 us; anything above +5 % is rejected and the shot repeated.
    const unsigned long max_fill_ns = 4095ul * 40ul * 105ul / 100ul;
    int r = 1, tries = 0; bool fired = false;
    while (r == 1 && tries < 8) {
        tries++;
        link_flush_rx();
        if (!pulser_arm(hi, lo, dead, false, &pc)) { printf("pe: pulse too long\n"); return; }
        snprintf(hdr, sizeof hdr, "ACQ 4 0 %d 1\n", in);
        link_puts(hdr);
        snprintf(note, sizeof note, "pulse-echo: pulse on RDY rise (+5V %.0f / off %.0f / GND %.0f ns), in=%d %s, 40 ns/sample; %s; try %d",
                 cyc_ns(pc.hi), cyc_ns(pc.dead), cyc_ns(pc.lo), in, acq_in_name(in), g, tries);
        r = acq_receive(hdr, sizeof hdr, note, max_fill_ns);
        fired = pulser_fired();
        pulser_disarm();
        if (r == 1) { sleep_ms(2); if (tries == 3) pic_relock(); }   // a different start phase next time; re-lock after 3
    }
    if (r == 1) printf("pe: %d shots, every capture had a non-uniform (slow) sample clock — nothing printed\n", tries);
    printf("# pulse %s, %d shot(s)\n", fired ? "fired" : "did NOT fire (no RDY edge)", tries);
}
// gain [leg [u1 [u2]]]: leg 0..3 = 4052 Rf on both stages (2.2k/4.7k/6.8k/10k), u1/u2 = 1 -> that op amp at x1 (UGE)
static void cmd_gain(const char *arg) {
    if (arg && *arg) {
        char *e; unsigned leg = (unsigned)strtoul(arg, &e, 10), u1 = 0, u2 = 0;
        if (*e == ' ') { u1 = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') u2 = (unsigned)strtoul(e + 1, NULL, 10); }
        if (leg > 3 || u1 > 1 || u2 > 1) { printf("usage: gain [leg 0..3 [u1 0|1 [u2 0|1]]]   leg: Rf 2.2k/4.7k/6.8k/10k (x3.2/x5.7/x7.8/x11 per stage); u = 1: that stage x1\n"); return; }
        char tx[24], rx[48]; snprintf(tx, sizeof tx, "UGE %u %u\n", u1, u2);
        link_flush_rx(); link_puts(tx);
        if (link_readline(rx, sizeof rx, LINK_TIMEOUT_US) < 0 || strncmp(rx, tx, strlen(tx) - 1)) { printf("gain: PIC did not confirm '%s' (got '%s')\n", "UGE", rx); return; }
        gpio_put(MINUS_PIN_GC1, leg & 1u); gpio_put(MINUS_PIN_GC2, (leg >> 1) & 1u);
        gain_leg = leg; gain_u1 = u1; gain_u2 = u2;
        sleep_ms(5);   // let the AC coupling (C1, C43/C44) settle after the switch
    }
    char d[160]; gain_desc(d, sizeof d); printf("%s\n", d);
}
static unsigned gain_u1_cur(void) { return gain_u1; }
static unsigned gain_leg_cur(void) { return gain_leg; }
static unsigned gain_u2_cur(void) { return gain_u2; }
// pc [0|1]: PIC-side period-4 fixed-pattern correction (on at PIC boot) off/on; prints state + the last capture's offsets
static void cmd_pc(const char *arg) {
    char tx[16], rx[64];
    if (arg && *arg) { if (strcmp(arg, "0") && strcmp(arg, "1")) { printf("usage: pc [0|1]\n"); return; } snprintf(tx, sizeof tx, "PC %s\n", arg); }
    else snprintf(tx, sizeof tx, "PC?\n");
    link_flush_rx(); link_puts(tx);
    if (link_readline(rx, sizeof rx, LINK_TIMEOUT_US) < 0) { printf("pc: no reply\n"); return; }
    int on; long o[4];
    if (sscanf(rx, "PC %d %ld %ld %ld %ld", &on, &o[0], &o[1], &o[2], &o[3]) != 5) { printf("pc: bad reply '%s'\n", rx); return; }
    printf("pattern correction %s; last capture offsets (LSB, phase 0..3): %+.2f %+.2f %+.2f %+.2f\n", on ? "ON" : "off",
           o[0] / 16.0, o[1] / 16.0, o[2] / 16.0, o[3] / 16.0);
}
static void cmd_acqcpu(const char *arg) {
    // acqcpu [trg [rptcnt]]: CPU-loop capture on the PIC (no DMA). trg 2 = back-to-back conversions (period
    // 32 ns at samc 0, 64 ns at samc 1, ...), trg 3 = ADC repeat timer every (rptcnt+1) x 16 ns (TAD at the 250 MHz ADC clock).
    char hdr[96]; unsigned trg = 12, r = 1, gap = 0, phase = 0;   // default: SCCP1 trigger at the last acq div (trg 2/3 proved dead in single-sample mode)
    if (arg && *arg) { char *e; trg = (unsigned)strtoul(arg, &e, 10); if (*e == ' ') { r = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') { gap = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') phase = (unsigned)strtoul(e + 1, NULL, 10); } } }
    if (r > 63 || trg > 31 || gap > 64 || phase > 15) { printf("acqcpu: trg 0..31, rptcnt 0..63, gap 0..64, phase 0..15\n"); return; }
    link_flush_rx();
    snprintf(hdr, sizeof hdr, "ACQCPU %u %u %u %u\n", trg, r, gap, phase);
    link_puts(hdr);
    char note[160];
    if (trg == 3) snprintf(note, sizeof note, "CPU-loop reader (no DMA, +%u NOPs per read), ADC repeat timer %u x 16 ns = %.1f ns; last input/samc", gap, r + 1, (r + 1) * 16.0);
    else snprintf(note, sizeof note, "CPU-loop reader (no DMA, +%u NOPs per read, phase %u), trigger %u (12 = SCCP1 at the last acq div; 2 back-to-back / 3 repeat timer are dead); last input/samc", gap, phase, trg);
    acq_receive(hdr, sizeof hdr, note, 0);
}
static void cmd_acqil(const char *arg) {
    // acqil [div [off [navg]]]: two ADC1 channels on the same input, each summing navg (default 2) 32 ns
    // conversions per trigger, triggered half a period apart (CH0 SCCP1, CH1 SCCP2 preloaded by off counts),
    // two DMA channels; the PIC interleaves the halves. div = per-channel period in 5 ns counts (default 24 = 120 ns ->
    // 16.7 M sums/s total; two DMA transfers per 120 ns leave 40 ns of margin at the 40 ns DMA cost). Uses the last acq input/samc.
    char hdr[96]; unsigned div = 24, off = 0, navg = 2;
    if (arg && *arg) { char *e; div = (unsigned)strtoul(arg, &e, 10); if (*e == ' ') { off = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') navg = (unsigned)strtoul(e + 1, NULL, 10); } }
    if (div < 4 || div > 255 || off > 255 || navg < 1 || navg > 16) { printf("acqil: div 4..255, off 0..255 (0 = div/2+1), navg 1..16\n"); return; }
    link_flush_rx();
    snprintf(hdr, sizeof hdr, "ACQIL %u %u %u\n", div, off, navg);
    link_puts(hdr);
    char note[200];
    snprintf(note, sizeof note, "two-channel interleave: per-channel period %u x 5 ns = %.1f ns, CH1 offset %s counts, each value = sum of %u conversions (%u bits); last input/samc",
             div, div * 5.0, off ? "given" : "div/2+1", navg, 12 + (navg >= 16 ? 4 : navg >= 8 ? 3 : navg >= 4 ? 2 : navg >= 2 ? 1 : 0));
    acq_receive(hdr, sizeof hdr, note, 0);
}
// Returns 0 = printed, 1 = fill longer than max_fill_ns (payload drained, NOT printed; caller retries), -1 = error.
// max_fill_ns 0 = no check.
static int acq_receive(char *hdr, unsigned hdrlen, const char *note, unsigned long max_fill_ns) {
    // RP-side timing of the capture window: the PIC holds RDY high from trigger start to DMA done.
    absolute_time_t t_arm = make_timeout_time_ms(100); int64_t rp_fill_us = -1;
    while (gpio_get(MINUS_PIN_RDY) && !time_reached(t_arm)) tight_loop_contents();     // PIC drops RDY when it parses ACQ
    while (!gpio_get(MINUS_PIN_RDY) && !time_reached(t_arm)) tight_loop_contents();    // then raises it at trigger start
    if (gpio_get(MINUS_PIN_RDY)) rp_fill_us = rdy_window(get_absolute_time());   // + the tgc schedule, if any
    int n = link_readline(hdr, hdrlen, 500000);                      // capture itself takes ~0.1 ms, deadline 5 ms
    if (n < 0) { printf("acq: no reply from PIC\n"); return -1; }
    if (!strncmp(hdr, "ERR", 3)) { printf("acq: PIC replied '%s'\n", hdr); return -1; }
    acq_hdr_t h;
    if (!acq_parse_header(hdr, &h)) { printf("acq: bad header '%s'\n", hdr); return -1; }
    char rate[64]; acq_format_rate(&h, rate, sizeof rate);
    if (!strcmp(h.status, "slow") && max_fill_ns) return 1;     // PIC flagged the 40/60/60 ns lock: caller re-shoots (no payload)
    if (strcmp(h.status, "ok") != 0) { printf("acq: status=%s (%s) — no payload\n", h.status, rate); return -1; }
    if (h.n == 0 || h.n > ACQ_MAX_N) { printf("acq: n=%u out of range\n", h.n); return -1; }   // parser already bounds it
    if (max_fill_ns && (unsigned long long)h.ticks * h.tick_ns > max_fill_ns) return 1;   // non-uniform: re-shoot, no fetch
    char info[112];
    const uint8_t *payload = link_fetch(h.n, info, sizeof info);   // proto 11: the RP pulls the payload (SPI, UART fallback)
    if (!payload) return -1;
    char tg[96]; tgc_desc(tg, sizeof tg);
    printf("# acq n=%u %s rp_fill=%lldus (RDY window timed by the RP crystal) %s%s %s\n", h.n, rate, (long long)rp_fill_us, note, tg, info);
    print_samples(payload, h.n);       // text or base64 (fmt); 4 KB blocks (one printf per line ran at ~200 kB/s)
    return 0;
}

// ---------------------------------------------------------------- ADC extras for pulse-echo (proto 13, pic >= 1.1.3)
// Design: docs/claude/specs/2026-11-22-adc-extras-design.md. tof / env fire the pulser on the PIC's RDY rise like pe.
#define PE_HI_NS 200u
#define PE_LO_NS 500u
#define PE_DEAD_NS 27u
// send one PIC command that captures (TOF / ENV), pulse armed on RDY when pulse != 0; retries 'slow' captures (<= 8, RELOCK after
// 3). Returns 0 with the reply in rx, -1 on error (printed). *fired = pulse seen.
static int pe_ext_shot(const char *tx, bool pulse, char *rx, unsigned rxlen, bool *fired) {
    pulse_cyc_t pc; int tries = 0;
    for (;;) {
        tries++;
        link_flush_rx();
        if (pulse && !pulser_arm(PE_HI_NS, PE_LO_NS, PE_DEAD_NS, false, &pc)) { printf("pulser arm failed\n"); return -1; }
        link_puts(tx);
        absolute_time_t t_arm = make_timeout_time_ms(100);                       // RDY: low when the PIC parses, high = capture
        while (gpio_get(MINUS_PIN_RDY) && !time_reached(t_arm)) tight_loop_contents();
        while (!gpio_get(MINUS_PIN_RDY) && !time_reached(t_arm)) tight_loop_contents();
        if (gpio_get(MINUS_PIN_RDY)) (void)rdy_window(get_absolute_time());       // runs the tgc schedule, if any
        int n = link_readline(rx, rxlen, 500000);
        if (fired) *fired = pulse && pulser_fired();
        if (pulse) pulser_disarm();
        if (n < 0) { printf("no reply from the PIC to '%.20s'\n", tx); return -1; }
        size_t L = strlen(rx);
        bool slow = L >= 5 && !strcmp(rx + L - 5, " slow");
        if (!slow) return 0;
        if (tries >= 8) { printf("%d captures, every one slow — nothing to report\n", tries); return -1; }
        if (tries == 3) pic_relock();
        sleep_ms(2);
    }
}
// acqos <4|16> [in [pe]]: hardware oversampling (13 / 14-bit, 175 / 565 ns per sample = 0.72 / 2.3 ms window); pe 1 = pulse on RDY
static void cmd_acqos(const char *arg) {
    unsigned os = 0, pe = 0; int in = 25; char hdr[96];
    if (!arg || sscanf(arg, "%u %d %u", &os, &in, &pe) < 1 || (os != 4 && os != 16) || in < 0 || in > 31) {
        printf("usage: acqos <4|16> [in [pe]]   oversampling: each sample = 4 or 16 x 32 ns conversions (13 / 14-bit), in = input code (25 default, 19 = DAC), pe 1 = fire the pulser\n"
               "  one pulse, averaging inside each sample. NOT for 3.3 MHz RF: 5.5 / 1.8 Msps alias it (Nyquist 2.8 / 0.9 MHz) and the 128 / 512 ns average cancels it; use acq/pe (RF), env (echo strength), tof (range)\n"); return;
    }
    pulse_cyc_t pc; bool fired = false;
    link_flush_rx();
    if (pe && !pulser_arm(PE_HI_NS, PE_LO_NS, PE_DEAD_NS, false, &pc)) { printf("acqos: pulser arm failed\n"); return; }
    snprintf(hdr, sizeof hdr, "ACQOS %u %d\n", os, in);
    link_puts(hdr);
    char note[200];
    snprintf(note, sizeof note, "oversampling %u x 32 ns conversions per sample (%u-bit result, %s), in=%d %s; %s", os, os == 4 ? 13 : 14,
             os == 4 ? "0..8191 = 2 x a 12-bit code" : "0..16383 = 4 x a 12-bit code", in, acq_in_name(in), pe ? "pulse on RDY" : "no pulse");
    if (pe) printf("# acqos: 3.3 MHz echoes alias at %s Msps and average out over %u ns: for RF use pe, for echo strength env\n", os == 4 ? "5.5" : "1.8", os * 32u);
    acq_receive(hdr, sizeof hdr, note, 0);
    if (pe) { fired = pulser_fired(); pulser_disarm(); printf("# pulse %s, 1 shot(s)\n", fired ? "fired" : "did NOT fire (no RDY edge)"); }
}
// tof <thr> [blank_ns [in [ref]]]: pulse + capture, first sample after blank_ns with |x - ref| > thr (ref 0/omitted = capture mean)
static void cmd_tof(const char *arg) {
    unsigned thr = 0, blank_ns = 0, ref = 0; int in = 25;
    if (!arg || sscanf(arg, "%u %u %d %u", &thr, &blank_ns, &in, &ref) < 1 || thr == 0 || thr > 4095 || in < 0 || in > 31 || ref > 4095) {
        printf("usage: tof <thr> [blank_ns [in [ref]]]   pulse + first |x-ref| > thr after blank_ns (ref 0 = capture mean; 40 ns per sample)\n"); return;
    }
    char tx[64], rx[112]; bool fired = false;
    snprintf(tx, sizeof tx, "TOF %u %u %d %u\n", thr, blank_ns / 40u, in, ref);
    if (pe_ext_shot(tx, true, rx, sizeof rx, &fired) < 0) return;
    int idx, pidx; unsigned peak, rf, hw; unsigned long ticks; unsigned tick_ns; char st[12];
    if (sscanf(rx, "TOF %d %d %u %u %u %lu %u %11s", &idx, &pidx, &peak, &rf, &hw, &ticks, &tick_ns, st) != 8) { printf("tof: bad reply '%s'\n", rx); return; }
    if (strcmp(st, "ok")) { printf("tof: status %s\n", st); return; }
    double dt = ticks * (double)tick_ns / 4095.0;                  // ns per sample, measured
    if (idx < 0) printf("tof: none — no sample beyond +-%u LSB of ref %u after %u ns (hw comparator %s); dt=%.2fns; pulse %s\n",
                        thr, rf, blank_ns, hw ? (ref ? "tripped before the blank" : "tripped on 2048+-thr (ref auto)") : "quiet", dt, fired ? "fired" : "did NOT fire");
    else printf("tof: first crossing at sample %d = %.0f ns (%.1f mm round trip -> %.1f mm at 1540 m/s); peak %u LSB at sample %d (%.0f ns); "
                "ref %u (%s); hw comparator %s; dt=%.2fns; pulse %s\n", idx, idx * dt, idx * dt * 1.54e-3, idx * dt * 0.77e-3, peak, pidx, pidx * dt,
                rf, ref ? "given" : "capture mean; comparator on 2048+-thr", hw ? "tripped" : "quiet", dt, fired ? "fired" : "did NOT fire");
}
// env <dec> [shots [in]]: pulse + capture + on-PIC envelope (|x - mean| integrated over dec samples), averaged over shots, then pulled
static void cmd_env(const char *arg) {
    unsigned dec = 0, shots = 1; int in = 25;
    if (!arg || sscanf(arg, "%u %u %d", &dec, &shots, &in) < 1 || dec < 4 || dec > 64 || shots < 1 || shots > 1000 || in < 0 || in > 31) {
        printf("usage: env <dec 4..64> [shots 1..1000 [in]]   on-PIC envelope, |x-mean| over dec samples, averaged over shots (one pulse each)\n"); return;
    }
    char tx[48], rx[96]; unsigned n = 0, d = 0, sh = 0, tick_ns = 0, fired_n = 0; unsigned long ticks = 0; char st[12] = "";
    for (unsigned k = 0; k < shots; k++) {
        bool fired = false;
        snprintf(tx, sizeof tx, "ENV %u %d %u\n", dec, in, k ? 1u : 0u);
        if (pe_ext_shot(tx, true, rx, sizeof rx, &fired) < 0) return;
        if (sscanf(rx, "ENV %u %u %u %lu %u %11s", &n, &d, &sh, &ticks, &tick_ns, st) != 6 || strcmp(st, "ok")) { printf("env: bad reply '%s'\n", rx); return; }
        fired_n += fired;
    }
    char info[112];
    const uint8_t *p = link_fetch(n, info, sizeof info);
    if (!p) return;
    double dt = ticks * (double)tick_ns / 4095.0 * dec;
    char tg[96]; tgc_desc(tg, sizeof tg);
    printf("# env n=%u dec=%u shots=%u dt=%.2fns fill=%.1fus in=%d values=mean |x-mean| x16 (1/16 LSB) per %u samples; pulses fired %u/%u%s %s\n",
           n, d, sh, dt, ticks * (double)tick_ns / 1000.0, in, dec, fired_n, shots, tg, info);
    print_samples(p, n);
}

// ---------------------------------------------------------------- link / linktest / dac (proto 11)
static void link_status(void) {
    double kbps = lk_last_us > 0 ? lk_last_bytes * 1e3 / (double)lk_last_us : 0;
    printf("link: payload over %s; SPI0 %.3f MHz (PIC client max 25 MHz); frames ok=%lu frame errors=%lu uart fallbacks=%lu no-reply=%lu",
           link_use_spi ? "SPI (UART fallback)" : "UART", link_spi_hz / 1e6, (unsigned long)lk_frames, (unsigned long)lk_frame_err,
           (unsigned long)lk_fallback, (unsigned long)lk_noreply);
    if (lk_last_us >= 0) printf("; last frame %u B in %lld us (%.0f kB/s, incl. the SPIX request)", lk_last_bytes, (long long)lk_last_us, kbps);
    printf("\n");
}
static bool link_set_mhz(const char *s) {
    double mhz = atof(s);
    if (mhz < 0.1 || mhz > 25.0) { printf("link: MHz must be 0.1..25 (PIC SPI client limit)\n"); return false; }
    link_spi_hz = spi_set_baudrate(LINK_SPI, (unsigned)(mhz * 1e6 + 0.5));
    return true;
}
// link [uart | spi [MHz]]: payload path for acq/pe/acqcpu/acqil; no argument = show counters
static void cmd_link(const char *arg) {
    if (arg && *arg) {
        if (!strcmp(arg, "uart")) link_use_spi = false;
        else if (!strncmp(arg, "spi", 3) && (arg[3] == 0 || arg[3] == ' ')) {
            if (arg[3] == ' ' && !link_set_mhz(arg + 4)) return;
            link_use_spi = true;
        } else { printf("usage: link [uart | spi [MHz]]\n"); return; }
    }
    link_status();
}
// linktest [count [MHz]]: PIC fills its capture buffer with an LFSR pattern (XTEST), the RP pulls it over SPI count times
// and checks every word + CRC, then pulls the last one over the UART too and compares. No capture, no piezo needed.
static void cmd_linktest(const char *arg) {
    unsigned count = 10; char *e = NULL;
    if (arg && *arg) {
        count = (unsigned)strtoul(arg, &e, 10);
        if (*e == ' ' && !link_set_mhz(e + 1)) return;
    }
    if (count < 1 || count > 10000) { printf("usage: linktest [count 1..10000 [MHz 0.1..25]]\n"); return; }
    link_flush_rx();
    unsigned ok = 0, ferr = 0, werr_frames = 0, noreply = 0; unsigned long werr_words = 0;
    int64_t tsum = 0, tmin = INT64_MAX, tmax = 0, rsum = 0, wsum = 0; uint16_t seed = 1; char rx[64], why[80];
    absolute_time_t t_all = get_absolute_time();
    for (unsigned i = 0; i < count; i++) {
        seed = (uint16_t)((i * 7919u + 1u) & 0xFFFFu); if (!seed) seed = 1;
        char tx[24]; snprintf(tx, sizeof tx, "XTEST %u\n", (unsigned)seed);
        link_puts(tx);
        unsigned n = 0, sd = 0;
        if (link_readline(rx, sizeof rx, LINK_TIMEOUT_US) < 0 || sscanf(rx, "XTEST %u %u", &n, &sd) != 2 || n != LINK_MAX_N || sd != seed) {
            noreply++; printf("linktest %u: XTEST reply '%s'\n", i, rx); link_flush_rx(); continue;
        }
        const uint8_t *p; int64_t us;
        if (link_spi_fetch(n, &p, &us, why, sizeof why) != 0) { ferr++; printf("linktest %u: %s\n", i, why); link_flush_rx(); continue; }
        unsigned bad = link_count_lfsr_errors(p, n, seed);
        if (bad) { werr_frames++; werr_words += bad; }
        else ok++;
        tsum += us; if (us < tmin) tmin = us; if (us > tmax) tmax = us;
        rsum += lk_last_ready_us; wsum += lk_last_wire_us;
    }
    int64_t t_total = absolute_time_diff_us(t_all, get_absolute_time());
    unsigned bytes = LINK_FRAME_LEN(LINK_MAX_N);
    printf("linktest: %u frames of %u B at %.3f MHz: ok=%u frame errors=%u pattern errors=%u frames / %lu words, no reply=%u\n",
           count, bytes, link_spi_hz / 1e6, ok, ferr, werr_frames, werr_words, noreply);
    if (ok + werr_frames) {
        double mean = (double)tsum / (ok + werr_frames);
        printf("linktest: SPIX request+frame %.0f us mean (min %lld, max %lld) = %.0f kB/s; wire time alone %.0f us; %u frames in %.2f s\n",
               mean, (long long)tmin, (long long)tmax, bytes * 1e3 / mean, bytes * 8e6 / link_spi_hz, count, t_total / 1e6);
        printf("linktest: of which SPIX -> RDY %.0f us, SPI clocking %.0f us (mean)\n",
               (double)rsum / (ok + werr_frames), (double)wsum / (ok + werr_frames));
    }
    // the last pattern over the UART: must be identical
    int64_t us; why[0] = 0;
    if (link_uart_fetch(LINK_MAX_N, link_buf + 8, &us, why, sizeof why) == 0) {
        unsigned bad = link_count_lfsr_errors(link_buf + 8, LINK_MAX_N, seed);
        printf("linktest: same buffer over the UART: %s (%u word errors) in %.2f s\n", bad ? "DIFFERS" : "identical", bad, us / 1e6);
    } else printf("linktest: UART cross-check failed: %s\n", why);
}
// dac [off | dc <code> | tri <lo> <hi> <slope> | sine <hz> [amp [mid]]]: PIC DAC1 test signal on DACOUT1 (U9 pin 3 = AD2AN3:
// read it back with "acq 4 0 19"; board 3: H6.16, v1.2: also RP GPIO26/ADC0). Codes 205..3890 = 5..95 % of AVDD (3.3 V).
#define DAC_V(c) ((c) * 3.3 / 4095.0)
static void cmd_dac(const char *arg) {
    char tx[64], rx[96];
    const char *usage = "usage: dac [off | dc <code> | tri <lo> <hi> <slope> | sine <hz> [amp [mid]]]   codes 205..3890 (5..95 % of 3.3 V)\n";
    if (!arg || !*arg) snprintf(tx, sizeof tx, "DAC?\n");
    else if (!strcmp(arg, "off")) snprintf(tx, sizeof tx, "DAC 0\n");
    else if (!strncmp(arg, "dc ", 3)) snprintf(tx, sizeof tx, "DAC 1 %lu\n", strtoul(arg + 3, NULL, 0));
    else if (!strncmp(arg, "tri ", 4)) {
        unsigned lo, hi, slp;
        if (sscanf(arg + 4, "%u %u %u", &lo, &hi, &slp) != 3) { printf("%s", usage); return; }
        snprintf(tx, sizeof tx, "DAC 2 %u %u %u\n", lo, hi, slp);
    } else if (!strncmp(arg, "sine ", 5)) {
        double hz = 0; unsigned amp = 1500, mid = 2048;
        if (sscanf(arg + 5, "%lf %u %u", &hz, &amp, &mid) < 1) { printf("%s", usage); return; }
        snprintf(tx, sizeof tx, "DAC 3 %.3f %u %u\n", hz, amp, mid);
    } else { printf("%s", usage); return; }
    link_flush_rx(); link_puts(tx);
    if (link_readline(rx, sizeof rx, 500000) < 0) { printf("dac: no reply from the PIC\n"); return; }
    unsigned a, b, c, d; double hz;
    if (!strncmp(rx, "DAC ERR", 7)) { printf("dac: PIC refused (%s)%s", rx + 8, !strcmp(rx + 8, "args") ? "\n" : " — PLL2 / CLKGEN7 did not lock\n"); if (!strcmp(rx + 8, "args")) printf("%s", usage); return; }
    if (!strncmp(rx, "DAC 0", 5)) printf("dac: off\n");
    else if (sscanf(rx, "DAC 1 %u", &a) == 1) printf("dac: dc %u = %.3f V\n", a, DAC_V(a));
    else if (sscanf(rx, "DAC 2 %u %u %u", &a, &b, &c) == 3) {
        double half_us = (b - a) * 16.0 / c * 0.004;   // (hi-lo)*16/SLPDAT steps of T_DAC = 2/500 MHz = 4 ns
        printf("dac: triangle %u..%u (%.3f..%.3f V), slope %u (12.4 counts per 4 ns step) -> period ~%.2f us (%.2f kHz, nominal)\n",
               a, b, DAC_V(a), DAC_V(b), c, 2 * half_us, 1e3 / (2 * half_us));
    } else if (sscanf(rx, "DAC 3 %lf %u %u %u %u", &hz, &a, &b, &c, &d) == 5)
    {
        printf("dac: sine %.1f Hz, %u points, update every %.2f us, %.3f V +- %.3f V (codes %u +- %u)\n", hz, a, b * 0.005, DAC_V(d), DAC_V(c), d, c);
        printf("  note: each sine update is a DMA transfer that costs the capture DMA ~1 sample: acq/pe at 20-25 Msps come back 'slow'\n"
               "  (bench 2026-11-21). Use 'dac tri' (hardware, no bus traffic) as the reference during captures.\n");
    }
    else { printf("dac: unexpected reply '%s'\n", rx); return; }
    if (strncmp(rx, "DAC 0", 5)) printf("  read it back: acq 4 0 19   (AD2AN3 = DACOUT1, U9 pin 3; board 3: H6.16)\n");
}

static void help(void) {
    printf("minus v1.1 RP2354A CLI\n"
           "  version     firmware version, chip id, unique id\n"
           "  rgb R G B [pct]  set the RGB LED (0-255 each): LP5562 U5 over I2C (board 3) at pct %% brightness (0-100, default 25 = dim) + the WS2812/SK6812 line (devkit, unscaled), e.g. rgb 255 0 0 100\n"
           "  reboot      reset the RP2354; 'reboot dfu' = reboot into BOOTSEL/UF2 mode\n"
           "  ping        send PING n over UART0 (GPIO16/17), expect PONG n from the PIC32\n"
           "  auto|stop   ping every 500 ms / stop\n"
           "  reset       pulse PIC MCLR low via GPIO24 (needs R53 <= 470R, see README)\n"
           "  rdy         read RDY (GPIO7 <- PIC RA7)\n"
           "  trig        2 us pulse on TRIG (GPIO6 -> PIC RA0)\n"
           "  raw <text>  send <text>\\n to the PIC and print whatever comes back within 200 ms\n"
           "  stat        counters\n"
           "  lb          RP UART0 internal loopback self-test\n"
           "  acq [div [samc [in [navg]]]]  capture 4095 ADC samples on the PIC and print them; div = SCCP1 trigger period in 5 ns counts (4 default = 25 Msps: the 32 ns ADC takes every other 20 ns trigger, uniform 40 ns = the DMA cost; 10 = 20 Msps; 5..9 irregular, on the DMA edge), samc = ADC sampling 0..7 (0.5+2n TAD, default 0) or -1 auto, in = input code: 0..15 ADC1 PINSEL, 16..31 ADC2 (25 = AD2AN9 node, default; 9 = AD1AN9 devkit node, 0 OA1OUT, 1 OA1IN+, 17 OA2OUT), navg = 1 single conversion (default) or 2..16 back-to-back conversions summed per trigger (ADC at 40 Msps)\n"
           "  acqcpu [trg [rptcnt [gap [phase]]]]  experiment: CPU-loop capture (no DMA), 4 CPU cycles = 20 ns per read + gap NOPs (conversions are 32 ns: no integer lock since the 200 MHz clock change); trg 12 (default) = SCCP1 at the last acq div, trg 2 back-to-back / 3 repeat timer (dead in single-sample mode, kept for experiments); phase = NOPs before the loop (moves the read off the ADC result write; pairs in the data = wrong phase); uses the last acq input/samc\n"
           "  acqil [div [off [navg]]]  experiment: two ADC1 channels on the same input, navg-sums (default 2) each, triggered half a period apart (div = per-channel period in 5 ns counts, default 24; parked since the 200 MHz / 250 MHz-ADC clock change: two 2-sums of 32 ns conversions no longer fit in one period, needs the 320 MHz ADC clock from PLL2), two DMA channels, interleaved; off = CH1 timer preload in counts (0 = div/2+1)\n"
           "  raw AMP1 0|1  op amp 1 off/on on the PIC (on at boot)\n"
           "  raw AMP2 0|1  op amp 2 off/on on the PIC (off at boot): OA2IN+ = OA1OUT, gain 1 + R_AW(U11)/R49, OA2OUT = FE_A_OUT (J6.2 / RF13, AD2AN1)\n"
           "  pulse [hi [lo [dead]]]  one pulser shot now (board 3, GPIO8/9 -> U3 -> Q1/Q2): +5 V hi ns (200), both off dead ns (27, min 4 cycles), GND lo ns (500), then released\n"
           "  pe [hi [lo [in [dead]]]]  pulse-echo: pulser fires on the PIC's RDY rise = ADC start, 4095 samples at 25 Msps on in (25 = AD2AN9 node default; 0 OA1OUT, 1 LNA/OA1IN+, 17 OA2OUT)\n"
           "  gain [leg [u1 [u2]]]  RX gain (board 3): leg 0..3 = 4052 Rf 2.2k/4.7k/6.8k/10k on both stages (x3.2/x5.7/x7.8/x11 each, Rg 1k); u1/u2 = 1 -> OA1/OA2 at x1 (PIC UGE). No args = show\n"
           "  pc [0|1]    period-4 fixed-pattern correction on the PIC (acq/pe, single conversions; on at boot) + last offsets\n"
           "  i2c         scan the I2C0 bus (MCP4531 x2, MCP4728, OLED)\n"
           "  pot <0|1> [n]  MCP4531 wiper read / set 0..128: 0 = U11 (OA2 feedback: gain x1..x11, power-on 64 = ~x6), 1 = U18 (AD8338)\n"
           "  raw ADCBB n [ovs]  experiment: time n back-to-back ADC conversions (no DMA); reply ADCBB n ovs ticks tick_ns sum\n"
           "  pic ...     ICSP programmer: pic id | image | flash | verify | erase   (pic help)\n"
           "  link [uart|spi [MHz]]  capture payload path: SPI0 frame from the PIC (default, 12.5 MHz, CRC-checked, UART fallback) or UART only (0.7 s); no args = counters\n"
           "  linktest [count [MHz]]  SPI link self-test: PIC LFSR pattern pulled count times (default 10), every word + CRC checked, then once over the UART\n"
           "  dac [off | dc <code> | tri <lo> <hi> <slope> | sine <hz> [amp [mid]]]  PIC DAC1 test signal on DACOUT1 (U9 pin 3, read back with acq 4 0 19); codes 205..3890\n"
           "  acqos <4|16> [in [pe]]  capture with ADC hardware oversampling: 4 / 16 conversions per sample (13 / 14-bit, 175 / 565 ns per sample, 0.72 / 2.3 ms window); pe 1 = fire the pulser. NOT for 3.3 MHz RF: 5.5 / 1.8 Msps alias it (Nyquist 2.8 / 0.9 MHz) and the 128 / 512 ns average cancels it; use acq/pe (RF), env (echo strength), tof (range)\n"
           "  tof <thr> [blank_ns [in [ref]]]  pulse-echo time of flight on the PIC: first |x-ref| > thr after blank_ns (ADC comparator armed; ref 0 = capture mean), one line, no A-line transfer\n"
           "  env <dec> [shots [in]]  pulse-echo envelope computed on the PIC (|x-mean| over dec = 4..64 samples), averaged over shots (one pulse each), then pulled: 4095/dec values\n"
           "  fmt [text|b64]  sample output of acq/pe/acqos/env: one decimal per line (default) or '# b64 <bytes>' + base64 lines of u16 LE (2.2x smaller, the Python library uses it)\n"
           "  tgc [off | <t_us> <leg> ...]  time-gain steps: switch the 4052 gain leg (0..3) at up to 4 times after the pulse during each capture; the gain leg is restored after\n");
}

int main(void) {
    pulser_init();          // first: puts the pulser FETs in the off state (GPIO9 pad pull-down = Q1 on)
    gain_pins_init();       // 4052 selects driven low = leg 0 (what the pad pull-downs gave before)
    stdio_init_all();
    led_init(); led_rgb(0, 0, 40);
    pic_taps_init();
    link_init();
    link_spi_init();

    char line[96]; int len = 0;
    absolute_time_t next_auto = get_absolute_time();
    printf("\nminus v1.1 RP2354A. 'help' for commands.\n");
    while (true) {
        int c = getchar_timeout_us(1000);
        if (c != PICO_ERROR_TIMEOUT) {
            if (c == '\r' || c == '\n') {
                line[len] = 0; len = 0;
                if (!strcmp(line, "help") || !strcmp(line, "?")) help();
                else if (!strcmp(line, "version")) cmd_version();
                else if (!strncmp(line, "rgb", 3)) {
                    // rgb R G B [pct]: pct = LP5562 brightness in % (default 25 = dim), scales the PWM; WS2812 line unscaled
                    int r, g, b, pct = 25;
                    int na = sscanf(line + 3, "%d %d %d %d", &r, &g, &b, &pct);
                    if ((na == 3 || na == 4) && (unsigned)r < 256 && (unsigned)g < 256 && (unsigned)b < 256 && (unsigned)pct <= 100) {
                        manual_led = true; led_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b);
                        int lp = lp5562_rgb((uint8_t)((r * pct + 50) / 100), (uint8_t)((g * pct + 50) / 100), (uint8_t)((b * pct + 50) / 100));
                        printf("rgb %d %d %d %d%% (LP5562 0x30: %s)\n", r, g, b, pct, lp < 0 ? "not found" : "ok");
                    } else printf("usage: rgb R G B [pct]  (0-255 each; pct = LP5562 brightness 0-100 %%, default 25)\n");
                }
                else if (!strncmp(line, "reboot", 6)) cmd_reboot(line[6] == ' ' ? line + 7 : NULL);
                else if (!strncmp(line, "pic", 3) && (line[3] == 0 || line[3] == ' ')) cmd_pic(line[3] == ' ' ? line + 4 : NULL);
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
                else if (!strcmp(line, "i2c")) cmd_i2c();
                else if (!strncmp(line, "pot", 3) && (line[3] == 0 || line[3] == ' ')) cmd_pot(line[3] == ' ' ? line + 4 : "");
                else if (!strcmp(line, "lb")) {
            // RP UART0 internal loopback (UARTCR.LBE): proves the RP's own TX->RX path and link_readline
            hw_set_bits(&uart_get_hw(LINK_UART)->cr, UART_UARTCR_LBE_BITS);
            char rx[64]; link_flush_rx(); link_puts("LOOP 42\n");
            int n = link_readline(rx, sizeof rx, LINK_TIMEOUT_US);
            hw_clear_bits(&uart_get_hw(LINK_UART)->cr, UART_UARTCR_LBE_BITS);
            printf("uart0 loopback: %s\n", n < 0 ? "FAILED (nothing received)" : !strcmp(rx, "LOOP 42") ? "ok" : rx);
        }
        else if (!strncmp(line, "acqil", 5) && (line[5] == 0 || line[5] == ' ')) cmd_acqil(line[5] == ' ' ? line + 6 : "");
        else if (!strncmp(line, "acqos", 5) && (line[5] == 0 || line[5] == ' ')) cmd_acqos(line[5] == ' ' ? line + 6 : "");
        else if (!strncmp(line, "tof", 3) && (line[3] == 0 || line[3] == ' ')) cmd_tof(line[3] == ' ' ? line + 4 : "");
        else if (!strncmp(line, "env", 3) && (line[3] == 0 || line[3] == ' ')) cmd_env(line[3] == ' ' ? line + 4 : "");
        else if (!strncmp(line, "fmt", 3) && (line[3] == 0 || line[3] == ' ')) cmd_fmt(line[3] == ' ' ? line + 4 : "");
        else if (!strncmp(line, "tgc", 3) && (line[3] == 0 || line[3] == ' ')) cmd_tgc(line[3] == ' ' ? line + 4 : "");
        else if (!strncmp(line, "acqcpu", 6) && (line[6] == 0 || line[6] == ' ')) cmd_acqcpu(line[6] == ' ' ? line + 7 : "");
        else if (!strncmp(line, "acq", 3) && (line[3] == 0 || line[3] == ' ')) cmd_acq(line[3] == ' ' ? line + 4 : "");
        else if (!strncmp(line, "pe", 2) && (line[2] == 0 || line[2] == ' ')) cmd_pe(line[2] == ' ' ? line + 3 : "");
        else if (!strncmp(line, "pc", 2) && (line[2] == 0 || line[2] == ' ')) cmd_pc(line[2] == ' ' ? line + 3 : "");
        else if (!strncmp(line, "gain", 4) && (line[4] == 0 || line[4] == ' ')) cmd_gain(line[4] == ' ' ? line + 5 : "");
        else if (!strncmp(line, "pulse", 5) && (line[5] == 0 || line[5] == ' ')) cmd_pulse(line[5] == ' ' ? line + 6 : "");
        else if (!strncmp(line, "linktest", 8) && (line[8] == 0 || line[8] == ' ')) cmd_linktest(line[8] == ' ' ? line + 9 : "");
        else if (!strncmp(line, "link", 4) && (line[4] == 0 || line[4] == ' ')) cmd_link(line[4] == ' ' ? line + 5 : "");
        else if (!strncmp(line, "dac", 3) && (line[3] == 0 || line[3] == ' ')) cmd_dac(line[3] == ' ' ? line + 4 : "");
        else if (!strcmp(line, "stat")) printf("sent=%lu ok=%lu bad=%lu timeout=%lu\n",
                        (unsigned long)stat_sent, (unsigned long)stat_ok, (unsigned long)stat_bad, (unsigned long)stat_timeout);
                else if (len == 0 && line[0]) printf("unknown '%s' — try help\n", line);
            } else if (len < (int)sizeof line - 1) line[len++] = (char)c;
        }
        if (auto_ping && time_reached(next_auto)) { do_ping(true); next_auto = make_timeout_time_ms(500); }
    }
}
