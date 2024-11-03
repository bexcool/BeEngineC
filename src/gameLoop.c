#include "gameLoop.h"
#include "logger.h"
#include "renderer.h"
#include <SDL2/SDL_events.h>

int exitRequested = 0;

int startGameLoop() {
    LOG("Starting game loop...");

    SDL_Event event;
    
    while (!exitRequested)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exitRequested = 1;
            }
        }

        renderer_render();
    }

    return 0;
}