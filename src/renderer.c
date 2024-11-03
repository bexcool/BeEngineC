#include "SDL.h"
#include "logger.h"

SDL_Renderer *gameRenderer;
SDL_Window *gameWindow;

int renderer_init() {
    LOG("Initializing renderer...");

    LOG("Renderer: Creating SDL window...");
    gameWindow = SDL_CreateWindow(
        "Breaker",
        100,
        100,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if (gameWindow == NULL) {
        LOG_E("Renderer: Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    LOG("Renderer: SDL window created.");

    LOG("Renderer: Creating SDL renderer...");
    gameRenderer = SDL_CreateRenderer(
        gameWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (gameRenderer == NULL) {
        LOG_E("Renderer: Could not create renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    LOG("Renderer: SDL renderer created.");
    LOG("Renderer initialized.");

    return 0;
}

void renderer_render() {
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gameRenderer);

    SDL_SetRenderDrawColor(gameRenderer, 255, 0, 0, 255);
    SDL_Rect rect = {
    .x = 100,
    .y = 200,
    .w = 500,
    .h = 200
    };
    SDL_RenderFillRect(gameRenderer, &rect);

    SDL_RenderPresent(gameRenderer);
}