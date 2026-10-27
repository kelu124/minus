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
// Commands (type on the USB console):
//   help | version | rgb R G B | reboot [dfu] | ping | auto | stop | reset | rdy | trig | raw <text> | stat
//   pic id | pic image | pic flash | pic verify | pic erase     (ICSP programmer on GPIO21/22/24)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/regs/pads_bank0.h"
#include "hardware/address_mapped.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
#include "pico/unique_id.h"
#include "pico/bootrom.h"
#include "pico/version.h"
#include "hardware/structs/sysinfo.h"
#include "version.h"
#include "pic_icsp.h"
#include "pic_image.h"
#include "acq_parse.h"

#define LINK_UART      uart0
#define LINK_BAUD      115200
#define LINK_TIMEOUT_US 200000   // 200 ms for a one-line reply (PIC answers within ~1 ms)
#define LINK_IDLE_US    50000    // link_flush_rx: drain until the PIC has been silent this long
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

static void cmd_version(void) {
    char uid[2 * PICO_UNIQUE_BOARD_ID_SIZE_BYTES + 1];
    pico_get_unique_board_id_string(uid, sizeof uid);
    printf("%s %s proto %d (built " __DATE__ " " __TIME__ ", pico-sdk " PICO_SDK_VERSION_STRING ")\n", FW_NAME, FW_VERSION, PROTO_VERSION);
    printf("board: minus_devkit (hardware/minUS_10102026), flash %u kB\n", PICO_FLASH_SIZE_BYTES / 1024);
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
static void cmd_acq(const char *arg) {
    static uint8_t payload[2 * ACQ_MAX_N];
    char hdr[96];
    unsigned div = 0; int samc = -2;                                        // div 0 = PIC default; samc -2 = not given
    if (arg && *arg) { char *e; div = (unsigned)strtoul(arg, &e, 10); if (*e == ' ') samc = (int)strtol(e + 1, NULL, 10); }
    link_flush_rx();
    if (div && samc != -2) snprintf(hdr, sizeof hdr, "ACQ %u %d\n", div, samc);
    else if (div) snprintf(hdr, sizeof hdr, "ACQ %u\n", div);
    else snprintf(hdr, sizeof hdr, "ACQ\n");
    link_puts(hdr);
    // RP-side timing of the capture window: the PIC holds RDY high from trigger start to DMA done.
    absolute_time_t t_arm = make_timeout_time_ms(100); int64_t rp_fill_us = -1;
    while (gpio_get(MINUS_PIN_RDY) && !time_reached(t_arm)) tight_loop_contents();     // PIC drops RDY when it parses ACQ
    while (!gpio_get(MINUS_PIN_RDY) && !time_reached(t_arm)) tight_loop_contents();    // then raises it at trigger start
    if (gpio_get(MINUS_PIN_RDY)) {
        absolute_time_t t0 = get_absolute_time(), t_end = make_timeout_time_ms(20);
        while (gpio_get(MINUS_PIN_RDY) && !time_reached(t_end)) tight_loop_contents();
        rp_fill_us = absolute_time_diff_us(t0, get_absolute_time());
    }
    int n = link_readline(hdr, sizeof hdr, 500000);                  // capture itself takes ~0.1 ms, deadline 5 ms
    if (n < 0) { printf("acq: no reply from PIC\n"); return; }
    if (!strncmp(hdr, "ERR", 3)) { printf("acq: PIC replied '%s'\n", hdr); return; }
    acq_hdr_t h;
    if (!acq_parse_header(hdr, &h)) { printf("acq: bad header '%s'\n", hdr); return; }
    char rate[64]; acq_format_rate(&h, rate, sizeof rate);
    if (strcmp(h.status, "ok") != 0) { printf("acq: status=%s (%s) — no payload\n", h.status, rate); return; }
    if (h.n == 0 || h.n > ACQ_MAX_N) { printf("acq: n=%u out of range\n", h.n); return; }   // parser already bounds it
    unsigned want = 2 * h.n;
    absolute_time_t deadline = make_timeout_time_us(1500000);         // 8190 B at 115200 baud ~ 0.71 s
    unsigned got = 0;
    while (got < want && !time_reached(deadline))
        if (uart_is_readable(LINK_UART)) payload[got++] = (uint8_t)uart_getc(LINK_UART);
    if (got < want) { printf("acq: short payload, got %u of %u bytes\n", got, want); return; }
    printf("# acq n=%u %s rp_fill=%lldus (RDY window timed by the RP crystal) trigger div %u; AD1AN9, 12-bit unsigned\n", h.n, rate, (long long)rp_fill_us, div ? div : 4);
    for (unsigned i = 0; i < h.n; i++) printf("%u\n", (unsigned)payload[2 * i] | (unsigned)payload[2 * i + 1] << 8);
}

static void help(void) {
    printf("minus devkit RP2354A link test\n"
           "  version     firmware version, chip id, unique id\n"
           "  rgb R G B   set the WS2812/SK6812 colour (0-255 each), e.g. rgb 255 255 255\n"
           "  reboot      reset the RP2354; 'reboot dfu' = reboot into BOOTSEL/UF2 mode\n"
           "  ping        send PING n over UART0 (GPIO16/17), expect PONG n from the PIC32\n"
           "  auto|stop   ping every 500 ms / stop\n"
           "  reset       pulse PIC MCLR low via GPIO24 (needs R53 <= 470R, see README)\n"
           "  rdy         read RDY (GPIO7 <- PIC RA7)\n"
           "  trig        2 us pulse on TRIG (GPIO6 -> PIC RA0)\n"
           "  raw <text>  send <text>\\n to the PIC and print whatever comes back within 200 ms\n"
           "  stat        counters\n"
           "  lb          RP UART0 internal loopback self-test\n"
           "  acq [div [samc]]  capture 4095 ADC samples on the PIC (AD1AN9) and print them; div = SCCP1 trigger period in counts (4 default), samc = ADC sampling 0..7 (0.5+2n TAD, default 0) or -1 auto\n"
           "  pic ...     ICSP programmer: pic id | image | flash | verify | erase   (pic help)\n");
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
                else if (!strcmp(line, "version")) cmd_version();
                else if (!strncmp(line, "rgb", 3)) {
                    int r, g, b;
                    if (sscanf(line + 3, "%d %d %d", &r, &g, &b) == 3 && (unsigned)r < 256 && (unsigned)g < 256 && (unsigned)b < 256) {
                        manual_led = true; led_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b); printf("rgb %d %d %d\n", r, g, b);
                    } else printf("usage: rgb R G B (0-255)\n");
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
                else if (!strcmp(line, "lb")) {
            // RP UART0 internal loopback (UARTCR.LBE): proves the RP's own TX->RX path and link_readline
            hw_set_bits(&uart_get_hw(LINK_UART)->cr, UART_UARTCR_LBE_BITS);
            char rx[64]; link_flush_rx(); link_puts("LOOP 42\n");
            int n = link_readline(rx, sizeof rx, LINK_TIMEOUT_US);
            hw_clear_bits(&uart_get_hw(LINK_UART)->cr, UART_UARTCR_LBE_BITS);
            printf("uart0 loopback: %s\n", n < 0 ? "FAILED (nothing received)" : !strcmp(rx, "LOOP 42") ? "ok" : rx);
        }
        else if (!strncmp(line, "acq", 3) && (line[3] == 0 || line[3] == ' ')) cmd_acq(line[3] == ' ' ? line + 4 : "");
        else if (!strcmp(line, "stat")) printf("sent=%lu ok=%lu bad=%lu timeout=%lu\n",
                        (unsigned long)stat_sent, (unsigned long)stat_ok, (unsigned long)stat_bad, (unsigned long)stat_timeout);
                else if (len == 0 && line[0]) printf("unknown '%s' — try help\n", line);
            } else if (len < (int)sizeof line - 1) line[len++] = (char)c;
        }
        if (auto_ping && time_reached(next_auto)) { do_ping(true); next_auto = make_timeout_time_ms(500); }
    }
}
