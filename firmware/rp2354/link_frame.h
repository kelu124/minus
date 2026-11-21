// SPI link frame helpers (proto 11) — pure C so they are unit-tested on the host (tests/test_link_frame.c).
// Frame from the PIC (firmware/pic32/xfer.c): A5 5A 'M' '1', n u16 LE, seq u16 LE, 2n payload bytes (u16 LE samples),
// CRC-32/IEEE LE over everything before it. Proto 12: no UART announcement; the PIC raises RDY when the frame is ready.
#pragma once
#include <stdint.h>

#define LINK_MAX_N        4095u
#define LINK_FRAME_LEN(n) (8u + 2u * (n) + 4u)

typedef enum { LINK_OK = 0, LINK_EMAGIC, LINK_EHDR, LINK_ECRC, LINK_ELEN } link_err_t;

typedef struct {
    unsigned n, seq;
    uint32_t crc;
    const uint8_t *payload;   // points into the frame
} link_frame_t;

uint32_t   link_crc32(uint32_t crc, const uint8_t *p, unsigned n);   // CRC-32/IEEE, crc 0 to start
uint16_t   link_lfsr_next(uint16_t x);                                // Galois 0xB400 (PIC XTEST pattern)
#define LINK_ANY_SEQ (-1L)
// checks length, magic, n (from the ACQ header), seq (unless LINK_ANY_SEQ) and the trailing CRC
link_err_t link_frame_check(const uint8_t *f, unsigned len, unsigned n, long seq, link_frame_t *out);
unsigned   link_count_lfsr_errors(const uint8_t *payload, unsigned n, uint16_t seed);   // words != LFSR sequence
const char *link_err_name(link_err_t e);
