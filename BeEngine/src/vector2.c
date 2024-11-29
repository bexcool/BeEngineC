#include "vector2.h"

#include "SDL.h"

SDL_Rect vector2x2toSDL_Rect(Vector2 *v1, Vector2 *v2) {
    return (SDL_Rect){v1->x, v1->y, v2->x, v2->y};
}