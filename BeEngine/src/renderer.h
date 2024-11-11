#include "SDL.h"
#include "color.h"
#include "vector2.h"

extern SDL_Window *gameWindow;
extern SDL_Renderer *gameRenderer;

int renderer_init(const char* projectName);
void renderer_render();

void renderer_fillRectangle(const Color *color, const Vector2 *position, const Vector2 *size);