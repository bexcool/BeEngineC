#include "engineCore.h"
#include "logger.h"
#include "renderer.h"

void cleanupApp() {
    LOG("Cleaning up...");

    // Destroy SDL window
    if (getRenderer()->gameWindow != NULL) {
        LOG("Destroying SDL window...");
        SDL_DestroyWindow(getRenderer()->gameWindow);
    }

    // Quit SDL
    LOG("Quitting SDL...");
    SDL_Quit();

    // Clean engine core
    LOG("Cleaning engine core...");
    _engineCore_clean();
}

void quitApp(int retCode) {
    LOG("Quitting application with code %d.", retCode);
    logger_stop();
    exit(retCode);
}