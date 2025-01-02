#include "gameLoop.h"

#include <SDL2/SDL_events.h>

#include "engineCore.h"
#include "logger.h"
#include "renderer.h"

int exitRequested = 0;

int gameLoop_start() {
    LOG("Starting game loop...");

    SDL_Event event;

    while (!exitRequested) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exitRequested = 1;
                    break;

                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        getRenderer()->event_viewportResized(&VECTOR2(event.window.data1, event.window.data2));
                    }
                    break;

                default:
                    break;
            }

            _engineCore_anyInput(&event);
        }

        _engineCore_tick();
        renderer_render();
    }

    LOG("Game loop: Exit requested. Starting the exit sequence...");

    return 0;
}