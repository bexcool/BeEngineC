#ifndef _VECTOR2_H_
#define _VECTOR2_H_

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

#define VECTOR2(_x, _y) \
    ((Vector2) {.x = _x, .y = _y})

#define VECTOR2_ZERO \
    ((Vector2) {.x = 0, .y = 0})

#endif