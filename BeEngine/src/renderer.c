#include "SDL.h"
#include "logger.h"
#include "appManager.h"
#include "objSquare.h"
#include "gameObject.h"
#include "engineCore.h"
#include "color.h"
#include "vector2.h"

SDL_Renderer *gameRenderer;
SDL_Window *gameWindow;

int renderer_init() {
    LOG("Initializing renderer...");

    EngineOptions opt = getCore()->options;

    LOG("Renderer: Creating SDL window...");
    gameWindow = SDL_CreateWindow(
        opt.projectName,
        opt.window_x,
        opt.window_y,
        opt.window_width,
        opt.window_height,
        SDL_WINDOW_SHOWN
    );

    if (gameWindow == NULL) {
        LOG_E("Renderer: Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    LOG("Renderer: SDL window created.");

    LOG("Renderer: Creating SDL renderer...");
    gameRenderer = SDL_CreateRenderer(
        gameWindow,
        -1,
        SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/
    );

    if (gameRenderer == NULL) {
        LOG_E("Renderer: Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }
    LOG("Renderer: SDL renderer created.");
    LOG("Renderer initialized.");

    return 0;
}

void renderer_render() {
    static size_t frame = 0;
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gameRenderer);

    Level *l = getLevel();

    for (size_t i = 0; i < l->allGameObjects.size; i++) {
        l->allGameObjects.items[i]->draw(l->allGameObjects.items[i]);
    }

    SDL_RenderPresent(gameRenderer);
}

void renderer_fillRectangle(const Color *color, const Vector2 *position, const Vector2 *size) {
    SDL_SetRenderDrawColor(gameRenderer, color->r, color->g, color->b, color->a);

    SDL_Rect rect = {
    .x = position->x,
    .y = position->y,
    .w = size->x,
    .h = size->y
    };

    SDL_RenderFillRect(gameRenderer, &rect);
}