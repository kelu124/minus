// RP2354 as ICSP programmer for the PIC32AK1216GC41048 (DS70005583 "Flash Programming Spec").
// Lines: GPIO21 = PGC1, GPIO22 = PGD1 (0R links), GPIO24 = MCLR node (needs R53 = 0R, JP1 cut).
#pragma once
#include <stdint.h>
#include <stdbool.h>

#define PIC_DEVID_ADDR   0x7C2000u
#define PIC_REVID_ADDR   0x7C2004u
#define PIC_DEVID_EXPECT 0x09DA2053u   // PIC32AK1216GC41048 (Table 1-5)

void     icsp_enter(void);                       // §2.2: MCLR low, key 0x8A12C2B2, MCLR high, 2x34 clocks
void     icsp_exit(void);                        // §2.3: MCLR low 1 ms, release everything to Hi-Z
bool     pic_read_id(uint32_t *devid, uint32_t *revid);
void     pic_read_block(uint32_t addr, uint32_t *words, unsigned n);   // §3.5, 32-bit aligned
bool     pic_bulk_erase(void);                   // §3.1 (code + UCA + UCB), false on timeout
bool     pic_program_quadwords(uint32_t addr, const uint8_t *data, unsigned len);   // §3.3, len % 16 == 0
uint32_t icsp_clocks(void);                      // statistics: PGC edges issued since enter
void     icsp_set_slow(bool on);                 // diagnostic: ~100 kHz PGC (entry key + all commands)
bool     icsp_get_slow(void);
uint32_t icsp_mclr_rise_us(void);                // diagnostic: MCLR node rise time after release (C31 check)
