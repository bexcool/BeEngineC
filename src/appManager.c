#include "SDL_image.h"
#include "SDL_mixer.h"
#include "engineCore.h"
#include "logger.h"
#include "renderer.h"

void cleanupApp() {
    LOG("Cleaning up...");

    // Cleaning font cache
    LOG("Cleaning font cache...");
    font_cleanup();

    // Destroy SDL window
    if (getRenderer()->gameWindow != NULL) {
        LOG("Destroying SDL window...");
        SDL_DestroyWindow(getRenderer()->gameWindow);
    }

    // Destroy SDL renderer
    if (getRenderer()->gameRenderer != NULL) {
        LOG("Destroying SDL renderer...");
        SDL_DestroyRenderer(getRenderer()->gameRenderer);
    }

    // Quit SDL_image
    LOG("Quitting SDL image...");
    IMG_Quit();

    // Quit SDL ttf
    LOG("Quitting SDL ttf...");
    TTF_Quit();

    // Quit SDL mixer
    LOG("Quitting SDL mixer...");
    Mix_CloseAudio();
    Mix_Quit();

    // Quit SDL
    LOG("Quitting SDL...");
    SDL_Quit();

    // Clean engine core
    LOG("Cleaning engine core...");
    _engineCore_clean();
}

void quitApp(int retCode) {
    cleanupApp();
    LOG("Quitting application with code %d.", retCode);
    logger_stop();
    exit(retCode);
}