#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "logger.h"
#include "gameLoop.h"
#include "renderer.h"
#include "helpers/fileHelper.h"
#include "SDL.h"

int main(int argc, char *argv[]) {
    logger_init(strcat(getParentDirectoryPath(argv[0]), "/log.txt"));

    #ifdef DEBUG
        LOG("Running in DEBUG configuration.");
    #endif

    #ifdef NDEBUG
        LOG("Running in RELEASE configuration.");
    #endif

    LOG("Starting application...");

    LOG("Initializing SDL...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG_E("Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    LOG("SDL initialized.");

    renderer_init();

    startGameLoop();
    
    LOG("Cleaning up...");
    LOG("Destroying SDL window...");
    SDL_DestroyWindow(gameWindow);
    LOG("Quitting SDL...");
    SDL_Quit();
    LOG("Stopping logger...");
    logger_stop();
    return 0;
}