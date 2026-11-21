// minus — PIC32AK capture payload transfer (proto 11). See xfer.h and docs/claude/specs/2026-11-21-dac-spi-link-design.md.
//
// SPI1 client on board 3 (no hardware change): SCK1 <- RP50 (RD1, net SPI_CLK = RP GPIO2), SDI1 <- RP51 (RD2, SPI_MOSI =
// GPIO3, not used: DISSDI), SS1 <- RP49 (RD0, SPI_CS = GPIO5), SDO1 -> RP35 (RC2, SPI_MISO -> GPIO4). Mode 1 since pic 1.1.2
// (CKP 0, CKE 0), 8-bit, enhanced buffer, MSB first. Client max SCK = 25 MHz with PPS pins (DS70005592 SP10, Table 40-35/36).
// The 16 KB RAM leaves no room for a frame copy, so the frame is streamed: header, acq_buf bytes (little-endian u16),
// CRC-32. The FIFO is fed by a CPU loop (>= 64 CPU cycles per byte even at 25 MHz) — the PIC has nothing else to do.
#include <xc.h>
#include <stdio.h>
#include "xfer.h"
#include "acq.h"

#define XFER_BUDGET 4000000u     // feed-loop iterations (~10 cycles each at 200 MHz) ~ 0.2 s worst case, then give up

static unsigned xfer_n;
static uint16_t xfer_seq;

void xfer_set_n(unsigned n) { xfer_n = n > ACQ_N ? ACQ_N : n; }
unsigned xfer_get_n(void) { return xfer_n; }

uint32_t crc32_update(uint32_t crc, const uint8_t *p, unsigned n) {
    static const uint32_t t[16] = {
        0x00000000u, 0x1DB71064u, 0x3B6E20C8u, 0x26D930ACu, 0x76DC4190u, 0x6B6B51F4u, 0x4DB26158u, 0x5005713Cu,
        0xEDB88320u, 0xF00F9344u, 0xD6D6A3E8u, 0xCB61B38Cu, 0x9B64C2B0u, 0x86D3D2D4u, 0xA00AE278u, 0xBDBDF21Cu };
    crc = ~crc;
    while (n--) { crc ^= *p++; crc = (crc >> 4) ^ t[crc & 15u]; crc = (crc >> 4) ^ t[crc & 15u]; }
    return ~crc;
}

uint16_t xfer_lfsr_next(uint16_t x) { return (uint16_t)((x >> 1) ^ ((x & 1u) ? 0xB400u : 0u)); }

void xfer_xtest(unsigned seed) {
    uint16_t x = (uint16_t)(seed ? seed : 1u);
    for (unsigned i = 0; i < ACQ_N; i++) { acq_buf[i] = x; x = xfer_lfsr_next(x); }
    xfer_n = ACQ_N;
}

static void spi_reset(void) {
    SPI1CON1bits.ON = 0;                    // clears the FIFOs and the shift register
    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SPITUR = 0;
    SPI1CON1bits.ON = 1;
}

void xfer_spi_init(void) {
    TRISDbits.TRISD0 = 1;                   // SS1  <- RP GPIO5
    TRISDbits.TRISD1 = 1;                   // SCK1 <- RP GPIO2
    TRISDbits.TRISD2 = 1;                   // SDI1 <- RP GPIO3 (ignored)
    TRISCbits.TRISC2 = 0;                   // SDO1 -> RP GPIO4
    SPI1CON1 = 0;
    SPI1CON2 = 0;                           // WLENGTH 0 = MODE32/MODE16 decide: 8-bit
    SPI1CON1bits.MSTEN  = 0;                // client
    SPI1CON1bits.SSEN   = 1;                // SS1 pin frames the transfer (SDO idle while SS is high)
    SPI1CON1bits.CKP    = 0;                // idle low  } RP SPI_CPOL_0 / SPI_CPHA_1 = mode 1 (pic 1.1.2): the RP PL022 in mode 0
    SPI1CON1bits.CKE    = 0;                // } pulses its frame signal between bytes (+1 bit each, ~19 %); mode 1 streams. Out on rising, RP samples on falling
    SPI1CON1bits.SMP    = 0;                // must be 0 in client mode
    SPI1CON1bits.ENHBUF = 1;                // FIFO
    SPI1CON1bits.DISSDI = 1;                // we only transmit
    SPI1CON1bits.IGNROV = 1;
    SPI1CON1bits.ON     = 1;
}

// Proto 12: no UART reply. The frame is announced on RDY (RA7 -> RP GPIO7, idle low after a capture): low while the
// FIFO is preloaded, high = "clock now", low again once the last byte left (or on timeout). The CRC is computed while
// feeding, so the RP can start clocking ~10 us after SPIX instead of after a full-buffer CRC + a 25-character reply.
#define RDY_LAT LATAbits.LATA7

static uint32_t crc_t[16] = {
    0x00000000u, 0x1DB71064u, 0x3B6E20C8u, 0x26D930ACu, 0x76DC4190u, 0x6B6B51F4u, 0x4DB26158u, 0x5005713Cu,
    0xEDB88320u, 0xF00F9344u, 0xD6D6A3E8u, 0xCB61B38Cu, 0x9B64C2B0u, 0x86D3D2D4u, 0xA00AE278u, 0xBDBDF21Cu };

int xfer_spix(void (*reply)(const char *), uint16_t *seq_out) {
    static uint8_t hdr[XFER_HDR];
    if (xfer_n == 0) { RDY_LAT = 0; reply("SPIX 0\n"); return -1; }
    RDY_LAT = 0;
    xfer_seq++;
    hdr[0] = XFER_MAGIC0; hdr[1] = XFER_MAGIC1; hdr[2] = XFER_MAGIC2; hdr[3] = XFER_MAGIC3;
    hdr[4] = (uint8_t)(xfer_n & 0xFFu); hdr[5] = (uint8_t)(xfer_n >> 8);
    hdr[6] = (uint8_t)(xfer_seq & 0xFFu); hdr[7] = (uint8_t)(xfer_seq >> 8);
    const uint8_t *pay = (const uint8_t *)acq_buf;
    unsigned nb = 2u * xfer_n, total = XFER_HDR + nb, i = 0;
    uint32_t crc = 0xFFFFFFFFu, budget = XFER_BUDGET;
    int raised = 0, r = 0;
    spi_reset();                            // start from an empty FIFO / shift register
    while (i < total) {                     // header + payload, CRC on the fly
        if (SPI1STATbits.SPITBF) {
            if (!raised) { RDY_LAT = 1; raised = 1; }    // FIFO full: the RP may clock
            if (--budget == 0) { r = -2; break; }
            continue;
        }
        uint8_t b = i < XFER_HDR ? hdr[i] : pay[i - XFER_HDR];
        SPI1BUF = b;
        crc ^= b; crc = (crc >> 4) ^ crc_t[crc & 15u]; crc = (crc >> 4) ^ crc_t[crc & 15u];
        i++;
    }
    crc = ~crc;
    for (unsigned k = 0; k < 4 && r == 0; ) {           // CRC-32 LE tail
        if (SPI1STATbits.SPITBF) {
            if (!raised) { RDY_LAT = 1; raised = 1; }
            if (--budget == 0) { r = -2; break; }
            continue;
        }
        SPI1BUF = (uint8_t)(crc >> (8 * k)); k++;
    }
    if (!raised) RDY_LAT = 1;               // tiny frame that fit in the FIFO
    if (r == 0) {                           // wait until the RP clocked the last byte out
        while ((SPI1STATbits.TXELM != 0 || !SPI1STATbits.SRMT) && --budget) ;
        if (!budget) r = -2;
    }
    RDY_LAT = 0;
    if (r != 0) spi_reset();                // timed out: drop what is left so the next frame starts clean
    if (seq_out) *seq_out = xfer_seq;
    return r;
}
