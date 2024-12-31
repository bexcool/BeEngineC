#include "vector2.h"

#include "SDL.h"

SDL_Rect vector2x2toSDL_Rect(Vector2 *v1, Vector2 *v2) {
    return (SDL_Rect){v1->x, v1->y, v2->x, v2->y};
}

Vector2 vector2_add(Vector2 *v1, Vector2 *v2) {
    return VECTOR2(v1->x + v2->x, v1->y + v2->y);
}

Vector2 vector2_sub(Vector2 *v1, Vector2 *v2) {
    return VECTOR2(v1->x - v2->x, v1->y - v2->y);
}

Vector2 vector2_mul(Vector2 *v1, float val) {
    return VECTOR2(v1->x * val, v1->y * val);
}

Vector2 vector2_div(Vector2 *v1, float val) {
    return VECTOR2(v1->x / val, v1->y / val);
}