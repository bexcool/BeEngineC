#include "color.h"

int color_equal(const Color *c1, const Color *c2) {
    return (c1->r == c2->r && c1->g == c2->g && c1->b == c2->b && c1->a == c2->a);
}

SDL_Color color_toSDL_Color(const Color *color) {
    return (SDL_Color){color->r, color->g, color->b, color->a};
}