// RP2354 as ICSP programmer for the PIC32AK1216GC41048 — a transcription of DS70005583 §2–3.
//
// Transport (§2.4): data LSB first, latched by the target on the PGC rising edge; the target drives
// PGD (reads) updating on PGC falling edges, we sample after the rising edge. 2-bit commands:
//   00 CMDEXEC  shift a 32-bit opcode, CPU executes it
//   01 CMDRD    target shifts VISI out
//   10 CMDSEQWR MOV.L #data, [W0++]
//   11 CMDSEQRD VISI out, then MOV.L [W0++], [W8]
// Timing (Table 2-3): period >= 60 ns, high/low >= 20 ns, setup >= 20 ns. We run ~1 MHz bit-banged.
#include "pic_icsp.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#ifndef MINUS_PIN_PIC_PGC
#include "boards/minus_devkit.h"
#endif
#define PGC  MINUS_PIN_PIC_PGC
#define PGD  MINUS_PIN_PIC_PGD
#define MCLR MINUS_PIN_PIC_MCLR

#define VISI    0x0007C0u
#define NVMCON  0x003000u

static uint32_t clocks;
uint32_t icsp_clocks(void) { return clocks; }

// ---------------------------------------------------------------- bit level
static inline void half(void) { busy_wait_at_least_cycles(60); }     // ~0.4 µs at 150 MHz
static inline void clk_pulse(void) { gpio_put(PGC, 1); half(); gpio_put(PGC, 0); half(); clocks++; }

static void shift_out(uint32_t v, unsigned nbits) {   // LSB first, data valid before rising edge
    for (unsigned i = 0; i < nbits; i++) {
        gpio_put(PGD, (v >> i) & 1u);
        busy_wait_at_least_cycles(10);                // >= 20 ns setup
        clk_pulse();
    }
}
static uint32_t shift_in32(void) {
    // one idle clock: tri-state PGD before its falling edge (target drives bit 0 from that edge)
    gpio_put(PGC, 1); half();
    gpio_set_dir(PGD, GPIO_IN);
    gpio_put(PGC, 0); half(); clocks++;
    uint32_t v = 0;
    for (unsigned i = 0; i < 32; i++) {
        gpio_put(PGC, 1); half();
        if (gpio_get(PGD)) v |= 1u << i;              // sample on/after the rising edge
        gpio_put(PGC, 0); half(); clocks++;           // target presents the next bit
    }
    // one idle clock: target releases PGD on the falling edge that ended bit 31
    gpio_put(PGC, 1); half(); gpio_put(PGC, 0); half(); clocks++;
    gpio_put(PGD, 0); gpio_set_dir(PGD, GPIO_OUT);
    return v;
}

// ---------------------------------------------------------------- commands
static void cmd_exec(uint32_t opcode)  { shift_out(0u, 2); shift_out(opcode, 32); }   // 00
static uint32_t cmd_rd(void)           { shift_out(1u, 2); return shift_in32(); }     // 01 -> bits "1" then "0"
static void cmd_seqwr(uint32_t data)   { shift_out(2u, 2); shift_out(data, 32); }     // 10 -> "0" then "1"
static uint32_t cmd_seqrd(void)        { shift_out(3u, 2); return shift_in32(); }     // 11

// MOV.SL #lit24, Wn  (0x80000003 | n<<26 | lit<<2): VISI->W8 = 0xA0001F03, NVMCON->W9 = 0xA400C003
static inline uint32_t op_movsl(unsigned wn, uint32_t lit24) { return 0x80000003u | ((uint32_t)wn << 26) | ((lit24 & 0xFFFFFFu) << 2); }

// ---------------------------------------------------------------- pins / mode
static void pins_drive(void) {
    gpio_init(PGC); gpio_put(PGC, 0); gpio_set_dir(PGC, GPIO_OUT);
    gpio_init(PGD); gpio_put(PGD, 0); gpio_set_dir(PGD, GPIO_OUT);
    gpio_set_slew_rate(PGC, GPIO_SLEW_RATE_SLOW); gpio_set_slew_rate(PGD, GPIO_SLEW_RATE_SLOW);
}
static void pins_release(void) {
    gpio_set_dir(PGC, GPIO_IN); gpio_disable_pulls(PGC);
    gpio_set_dir(PGD, GPIO_IN); gpio_disable_pulls(PGD);
}

void icsp_enter(void) {
    clocks = 0;
    gpio_init(MCLR); gpio_put(MCLR, 0); gpio_set_dir(MCLR, GPIO_OUT);   // 2. MCLR low
    pins_drive();                                                      // 3. PGC/PGD low
    sleep_ms(2);                                                       // 4. >= 1 ms
    gpio_put(MCLR, 1); busy_wait_at_least_cycles(30); gpio_put(MCLR, 0);  // 5. pulse >= 20 ns, << 2 µs
    busy_wait_us(2);
    shift_out(0x8A12C2B2u, 32);                                        // 6. key, LSB first
    gpio_put(MCLR, 1);                                                 // 7. after the 32nd falling edge
    sleep_us(600);                                                     // 8. >= 500 µs, PGC low
    shift_out(0u, 2); shift_out(0x00801000u, 32);                      // 9. 34 clocks
    shift_out(0u, 2); shift_out(0x00801000u, 32);                      // 10. 34 clocks
}

void icsp_exit(void) {
    gpio_put(MCLR, 0);                                                 // MCLR low
    pins_release();                                                    // tri-state PGC/PGD
    sleep_ms(2);                                                       // >= 1 ms
    gpio_set_dir(MCLR, GPIO_IN); gpio_disable_pulls(MCLR);             // let R5 pull it up -> user code runs
}

// ---------------------------------------------------------------- §3.5 read
void pic_read_block(uint32_t addr, uint32_t *words, unsigned n) {
    cmd_exec(op_movsl(8, VISI));
    cmd_exec(op_movsl(0, addr));
    (void)cmd_seqrd();                       // dummy: returns stale VISI, loads the first word
    for (unsigned i = 0; i < n; i++) words[i] = cmd_seqrd();
}

bool pic_read_id(uint32_t *devid, uint32_t *revid) {
    uint32_t w[2];
    pic_read_block(PIC_DEVID_ADDR, w, 2);
    if (devid) *devid = w[0];
    if (revid) *revid = w[1];
    return w[0] == PIC_DEVID_EXPECT;
}

// ---------------------------------------------------------------- WR polling (shared)
// Precondition: W8 = VISI, W9 = NVMCON, and a MOV.L [W9],[W8] has already been issued once.
static bool poll_wr_clear(uint32_t timeout_us) {
    absolute_time_t deadline = make_timeout_time_us(timeout_us);
    for (;;) {
        cmd_exec(0x83892400u);               // MOV.L [W9], [W8]  (completes the previous move too)
        uint32_t nvmcon = cmd_rd();
        if (!(nvmcon & 0x8000u)) return true;
        if (time_reached(deadline)) return false;
    }
}

// ---------------------------------------------------------------- §3.1 bulk erase
bool pic_bulk_erase(void) {
    cmd_exec(0xA0001F03u);                   // MOV.SL #VISI, W8
    cmd_exec(0xA400C003u);                   // MOV.SL #NVMCON, W9
    cmd_exec(0x8A9004E1u);                   // MOVS.W #0x400E, [W9]   (WREN | bulk erase)
    cmd_exec(0x8E9004E1u);                   // MOVS.W #0xC00E, [W9]   (WR)
    cmd_exec(0x83892400u);                   // MOV.L [W9], [W8]
    return poll_wr_clear(200000);            // spec max 20 ms (much longer if regions are protected)
}

// ---------------------------------------------------------------- §3.3 quadword program
bool pic_program_quadwords(uint32_t addr, const uint8_t *data, unsigned len) {
    if (len % 16 || addr % 16) return false;
    cmd_exec(0xA0001F03u);                   // MOV.SL #VISI, W8
    cmd_exec(0xA400C003u);                   // MOV.SL #NVMCON, W9
    cmd_exec(0x00000309u);                   // MOV.L W9, W0
    cmd_exec(0xA8030007u);                   // MOV.SL #0xC001, W10
    cmd_seqwr(0x00004001u);                  // NVMCON = 0x4001 (WREN | quadword), W0 -> NVMADR
    for (unsigned off = 0; off < len; off += 16) {
        cmd_seqwr(addr + off);               // NVMADR, W0 -> NVMDATA0
        for (unsigned k = 0; k < 4; k++) {
            const uint8_t *p = data + off + 4 * k;
            cmd_seqwr((uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24);
        }
        cmd_exec(0x1F0A0309u);               // MOV.L W9, W0 ; MOV.L W10, [W0++]  -> NVMCON = 0xC001 (WR), W0 -> NVMADR
        cmd_exec(0x83892400u);               // MOV.L [W9], [W8]
        if (!poll_wr_clear(5000)) return false;   // spec max 15 µs per quadword
    }
    return true;
}
