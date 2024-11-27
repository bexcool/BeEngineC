
#include <SDL2/SDL.h>

#include "color.h"
#include "vector2.h"

extern SDL_Window *gameWindow;
extern SDL_Renderer *gameRenderer;

int renderer_init();
void renderer_render();

void renderer_fillRectangle(const Color *color, const Vector2 *position, const Vector2 *size);