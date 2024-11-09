#include "renderer.h"
#include "logger.h"

void cleanupApp() {
    LOG("Cleaning up...");

    // Destroy SDL window
    if (gameWindow != NULL) {
        LOG("Destroying SDL window...");
        SDL_DestroyWindow(gameWindow);
    }

    // Quit SDL
    LOG("Quitting SDL...");
    SDL_Quit();
}

void quitApp(int retCode) {
    LOG("Quitting application with code %d.", retCode);
    logger_stop();
    exit(retCode);
}