// Host test for the SPI link frame helpers (plain C, no pico-sdk).
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "link_frame.h"

static void test_crc32_check_value(void) {
    const char *s = "123456789";
    assert(link_crc32(0, (const uint8_t *)s, 9) == 0xCBF43926u);           // CRC-32/IEEE check value
    // incremental == one-shot
    uint32_t c = link_crc32(0, (const uint8_t *)s, 4);
    assert(link_crc32(c, (const uint8_t *)s + 4, 5) == 0xCBF43926u);
}

static void test_lfsr_sequence(void) {
    // Galois 0xB400: from 1 -> 0xB400 -> 0x5A00 -> 0x2D00 ...; period 65535, never 0
    assert(link_lfsr_next(1) == 0xB400u);
    assert(link_lfsr_next(0xB400u) == 0x5A00u);
    uint16_t x = 1; unsigned i = 0;
    do { x = link_lfsr_next(x); i++; assert(x != 0); } while (x != 1 && i < 70000u);
    assert(i == 65535u);
}

static unsigned make_frame(uint8_t *f, unsigned n, unsigned seq, uint16_t seed) {
    f[0] = 0xA5; f[1] = 0x5A; f[2] = 'M'; f[3] = '1';
    f[4] = (uint8_t)n; f[5] = (uint8_t)(n >> 8); f[6] = (uint8_t)seq; f[7] = (uint8_t)(seq >> 8);
    uint16_t x = seed;
    for (unsigned i = 0; i < n; i++) { f[8 + 2 * i] = (uint8_t)x; f[9 + 2 * i] = (uint8_t)(x >> 8); x = link_lfsr_next(x); }
    uint32_t c = link_crc32(0, f, 8 + 2 * n);
    for (unsigned k = 0; k < 4; k++) f[8 + 2 * n + k] = (uint8_t)(c >> (8 * k));
    return LINK_FRAME_LEN(n);
}

static void test_frame_check_ok_and_errors(void) {
    static uint8_t f[LINK_FRAME_LEN(4095)];
    unsigned len = make_frame(f, 4095, 7, 1);
    assert(len == 8202u);
    uint32_t crc = link_crc32(0, f, len - 4);
    link_frame_t fr;
    assert(link_frame_check(f, len, 4095, 7, crc, &fr) == LINK_OK);
    assert(fr.n == 4095 && fr.seq == 7 && fr.crc == crc);
    assert(fr.payload == f + 8);
    assert(link_count_lfsr_errors(fr.payload, 4095, 1) == 0);

    f[100] ^= 0x10;                                                    // one flipped bit
    assert(link_frame_check(f, len, 4095, 7, crc, &fr) == LINK_ECRC);
    assert(link_count_lfsr_errors(f + 8, 4095, 1) == 1);
    f[100] ^= 0x10;

    f[0] = 0xFF;
    assert(link_frame_check(f, len, 4095, 7, crc, &fr) == LINK_EMAGIC);
    f[0] = 0xA5;
    assert(link_frame_check(f, len, 4094, 7, crc, &fr) == LINK_EHDR);  // n disagrees with the UART reply
    assert(link_frame_check(f, len, 4095, 8, crc, &fr) == LINK_EHDR);  // seq disagrees
    assert(link_frame_check(f, len, 4095, 7, crc ^ 1u, &fr) == LINK_ECRC); // reply CRC disagrees
}

static void test_parse_spix_reply(void) {
    unsigned n, seq; uint32_t crc;
    assert(link_parse_spix("SPIX 4095 12 CBF43926", &n, &seq, &crc) == 1);
    assert(n == 4095 && seq == 12 && crc == 0xCBF43926u);
    assert(link_parse_spix("SPIX 0", &n, &seq, &crc) == 0);
    assert(link_parse_spix("ERR", &n, &seq, &crc) == 0);
    assert(link_parse_spix("SPIX 5000 1 0", &n, &seq, &crc) == 0);       // larger than the RP buffer
}

int main(void) {
    test_crc32_check_value();
    test_lfsr_sequence();
    test_frame_check_ok_and_errors();
    test_parse_spix_reply();
    printf("test_link_frame: all passed\n");
    return 0;
}
