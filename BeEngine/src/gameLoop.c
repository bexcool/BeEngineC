#include "gameLoop.h"
#include "logger.h"
#include "renderer.h"
#include "engineCore.h"
#include "physicsEngine.h"
#include <SDL2/SDL_events.h>

int exitRequested = 0;

int gameLoop_start() {
    LOG("Starting game loop...");

    SDL_Event event;
    
    while (!exitRequested)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exitRequested = 1;
            }

            if (getCore()->events.event_anyInput != NULL) getCore()->events.event_anyInput(&event);
        }

        _engineCore_tick();
        _physicsEngine_tick();
        renderer_render();
    }

    LOG("Game loop: Exit requested. Starting the exit sequence...");

    return 0;
}