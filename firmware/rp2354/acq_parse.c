#include "acq_parse.h"
#include <stdio.h>
#include <string.h>

int acq_parse_header(const char *line, acq_hdr_t *h) {
    if (!line || !h) return 0;
    memset(h, 0, sizeof *h);
    int got = sscanf(line, "ACQ %u %lu %u %11s", &h->n, &h->ticks, &h->tick_ns, h->status);
    return got == 4 && strncmp(line, "ACQ ", 4) == 0;
}

int acq_format_rate(const acq_hdr_t *h, char *buf, unsigned len) {
    // fill time in ns, printed as x.y us; rate in Msps with two decimals (integer math)
    unsigned long long fill_ns = (unsigned long long)h->ticks * h->tick_ns;
    unsigned long fill_tenths_us = (unsigned long)(fill_ns / 100ULL);         // 0.1 us units
    if (fill_ns == 0)
        return snprintf(buf, len, "fill=0.0us fs=?");
    unsigned long long fs_centi = (unsigned long long)h->n * 100000ULL / fill_ns;   // Msps x 100 = n*1000/fill_ns*100
    return snprintf(buf, len, "fill=%lu.%luus fs=%llu.%02lluMsps",
                    fill_tenths_us / 10, fill_tenths_us % 10, fs_centi / 100, fs_centi % 100);
}
