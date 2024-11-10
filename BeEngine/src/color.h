#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdint.h>

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

#define COLOR(red, green, blue) \
    ((Color) { .r = red, .g = green, .b = blue, .a = 255 })

#define COLOR_RGBA(red, green, blue, alpha) \
    ((Color) { .r = red, .g = green, .b = blue, .a = alpha } )

#endif