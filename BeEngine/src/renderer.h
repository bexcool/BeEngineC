#include <SDL2/SDL.h>

#include "array.h"
#include "color.h"
#include "vector2.h"

extern SDL_Window *gameWindow;
extern SDL_Renderer *gameRenderer;

#ifndef NDEBUG

extern int debugShowCollisions, debugShowStats;

#endif

int renderer_init();
void renderer_render();

void renderer_drawFillRectangle(const Color *color, const Vector2 *location, const Vector2 *size);
void renderer_drawRectangle(const Color *color, const Vector2 *location, const Vector2 *size);