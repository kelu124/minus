// Embedded PIC32AK flash image (generated at build time from firmware/pic32/build/minus_pic.hex).
#pragma once
#include <stdint.h>
typedef struct { uint32_t addr; uint32_t len; const uint8_t *data; } pic_segment_t;   // len % 16 == 0
extern const pic_segment_t pic_image_segments[];   // terminated by {0,0,0}
extern const unsigned pic_image_nseg;
extern const unsigned pic_image_bytes;
extern const char pic_image_name[];
