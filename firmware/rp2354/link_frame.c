// SPI link frame helpers (proto 11). See link_frame.h.
#include <stdio.h>
#include <string.h>
#include "link_frame.h"

uint32_t link_crc32(uint32_t crc, const uint8_t *p, unsigned n) {
    static const uint32_t t[16] = {
        0x00000000u, 0x1DB71064u, 0x3B6E20C8u, 0x26D930ACu, 0x76DC4190u, 0x6B6B51F4u, 0x4DB26158u, 0x5005713Cu,
        0xEDB88320u, 0xF00F9344u, 0xD6D6A3E8u, 0xCB61B38Cu, 0x9B64C2B0u, 0x86D3D2D4u, 0xA00AE278u, 0xBDBDF21Cu };
    crc = ~crc;
    while (n--) { crc ^= *p++; crc = (crc >> 4) ^ t[crc & 15u]; crc = (crc >> 4) ^ t[crc & 15u]; }
    return ~crc;
}

uint16_t link_lfsr_next(uint16_t x) { return (uint16_t)((x >> 1) ^ ((x & 1u) ? 0xB400u : 0u)); }

link_err_t link_frame_check(const uint8_t *f, unsigned len, unsigned n, long seq, link_frame_t *out) {
    if (len < LINK_FRAME_LEN(0)) return LINK_ELEN;
    if (f[0] != 0xA5u || f[1] != 0x5Au || f[2] != 'M' || f[3] != '1') return LINK_EMAGIC;
    unsigned fn = (unsigned)f[4] | (unsigned)f[5] << 8, fs = (unsigned)f[6] | (unsigned)f[7] << 8;
    if (fn != n || (seq >= 0 && fs != ((unsigned long)seq & 0xFFFFu))) return LINK_EHDR;
    if (len != LINK_FRAME_LEN(n)) return LINK_ELEN;
    uint32_t c = link_crc32(0, f, len - 4), tail = 0;
    for (unsigned k = 0; k < 4; k++) tail |= (uint32_t)f[len - 4 + k] << (8 * k);
    if (c != tail) return LINK_ECRC;
    if (out) { out->n = fn; out->seq = fs; out->crc = c; out->payload = f + 8; }
    return LINK_OK;
}

unsigned link_count_lfsr_errors(const uint8_t *payload, unsigned n, uint16_t seed) {
    uint16_t x = seed ? seed : 1u; unsigned bad = 0;
    for (unsigned i = 0; i < n; i++) {
        uint16_t w = (uint16_t)(payload[2 * i] | payload[2 * i + 1] << 8);
        if (w != x) bad++;
        x = link_lfsr_next(x);
    }
    return bad;
}

const char *link_err_name(link_err_t e) {
    switch (e) {
    case LINK_OK: return "ok"; case LINK_EMAGIC: return "magic"; case LINK_EHDR: return "header";
    case LINK_ECRC: return "crc"; case LINK_ELEN: return "length"; default: return "?";
    }
}

unsigned link_b64_encode(const uint8_t *in, unsigned n, char *out) {
    static const char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned o = 0;
    for (unsigned i = 0; i < n; i += 3) {
        uint32_t v = (uint32_t)in[i] << 16;
        if (i + 1 < n) v |= (uint32_t)in[i + 1] << 8;
        if (i + 2 < n) v |= in[i + 2];
        out[o++] = a[(v >> 18) & 63]; out[o++] = a[(v >> 12) & 63];
        out[o++] = i + 1 < n ? a[(v >> 6) & 63] : '=';
        out[o++] = i + 2 < n ? a[v & 63] : '=';
    }
    out[o] = 0;
    return o;
}
