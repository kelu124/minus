// minus — PIC32AK capture payload transfer: SPI1 client frames (proto 11) + UART fallback + link self-test.
// Design: docs/claude/specs/2026-11-21-dac-spi-link-design.md
#ifndef XFER_H
#define XFER_H
#include <stdint.h>

#define XFER_MAGIC0 0xA5u
#define XFER_MAGIC1 0x5Au
#define XFER_MAGIC2 'M'
#define XFER_MAGIC3 '1'
#define XFER_HDR    8u        // magic[4], n u16 LE, seq u16 LE; then 2n payload bytes; then CRC-32 LE (4 bytes)

uint32_t crc32_update(uint32_t crc, const uint8_t *p, unsigned n);   // CRC-32/IEEE (reflected 0xEDB88320), crc 0 to start

void     xfer_spi_init(void);           // SPI1 client, mode 0, 8-bit, SS enabled (PPS set in main.c pps_init)
void     xfer_set_n(unsigned n);        // samples available in acq_buf for SPIX/UTX (0 = none)
unsigned xfer_get_n(void);
// SPIX (proto 12): drops RDY, preloads the TX FIFO, raises RDY ("clock now"), feeds header + payload + CRC (computed on the
// fly) until the RP clocked everything or the budget ran out, drops RDY. No UART reply, except "SPIX 0" when nothing is
// pending (reply). Returns 0 ok, -1 nothing to send, -2 timeout (SPI reset).
int      xfer_spix(void (*reply)(const char *), uint16_t *seq_out);
void     xfer_xtest(unsigned seed); // fill acq_buf[ACQ_N] with the 16-bit LFSR pattern (x ^= ..., Galois 0xB400), n = ACQ_N
uint16_t xfer_lfsr_next(uint16_t x);

#endif
