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
    // proto 12: n from the ACQ header, any seq, CRC from the frame tail only
    assert(link_frame_check(f, len, 4095, LINK_ANY_SEQ, &fr) == LINK_OK);
    assert(fr.n == 4095 && fr.seq == 7 && fr.crc == crc);
    assert(fr.payload == f + 8);
    assert(link_count_lfsr_errors(fr.payload, 4095, 1) == 0);
    assert(link_frame_check(f, len, 4095, 7, &fr) == LINK_OK);

    f[100] ^= 0x10;                                                    // one flipped bit
    assert(link_frame_check(f, len, 4095, LINK_ANY_SEQ, &fr) == LINK_ECRC);
    assert(link_count_lfsr_errors(f + 8, 4095, 1) == 1);
    f[100] ^= 0x10;
    f[len - 1] ^= 0x01;                                                // corrupted CRC tail
    assert(link_frame_check(f, len, 4095, LINK_ANY_SEQ, &fr) == LINK_ECRC);
    f[len - 1] ^= 0x01;

    f[0] = 0xFF;
    assert(link_frame_check(f, len, 4095, LINK_ANY_SEQ, &fr) == LINK_EMAGIC);
    f[0] = 0xA5;
    assert(link_frame_check(f, len, 4094, LINK_ANY_SEQ, &fr) == LINK_EHDR);  // n disagrees with the ACQ header
    assert(link_frame_check(f, len, 4095, 8, &fr) == LINK_EHDR);             // seq disagrees (when checked)
    assert(link_frame_check(f, 4, 4095, LINK_ANY_SEQ, &fr) == LINK_ELEN);
}

static void test_base64(void) {
    char out[64];
    assert(link_b64_encode((const uint8_t *)"", 0, out) == 0 && out[0] == 0);
    assert(link_b64_encode((const uint8_t *)"f", 1, out) == 4 && !strcmp(out, "Zg=="));
    assert(link_b64_encode((const uint8_t *)"fo", 2, out) == 4 && !strcmp(out, "Zm8="));
    assert(link_b64_encode((const uint8_t *)"foo", 3, out) == 4 && !strcmp(out, "Zm9v"));
    assert(link_b64_encode((const uint8_t *)"foobar", 6, out) == 8 && !strcmp(out, "Zm9vYmFy"));
    const uint8_t bin[4] = { 0x00, 0xFF, 0x10, 0x0F };
    assert(link_b64_encode(bin, 4, out) == 8 && !strcmp(out, "AP8QDw=="));
}

int main(void) {
    test_base64();
    test_crc32_check_value();
    test_lfsr_sequence();
    test_frame_check_ok_and_errors();
    printf("test_link_frame: all passed\n");
    return 0;
}
