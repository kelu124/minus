// acq header parsing / rate formatting — pure C so it is unit-tested on the host (tests/).
// PIC reply: "ACQ <n> <ticks> <tick_ns> <status>"  (status: ok | timeout | dmaerr | notready)
#pragma once

typedef struct {
    unsigned      n;         // samples announced
    unsigned long ticks;     // Timer1 ticks from trigger start to DMA done
    unsigned      tick_ns;   // Timer1 tick in ns
    char          status[12];
} acq_hdr_t;

int acq_parse_header(const char *line, acq_hdr_t *h);           // 1 = parsed, 0 = not an ACQ header
int acq_format_rate(const acq_hdr_t *h, char *buf, unsigned len); // "fill=102.4us fs=39.99Msps"; chars written
