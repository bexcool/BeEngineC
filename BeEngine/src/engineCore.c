#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "engineCore.h"
#include "logger.h"
#include "gameLoop.h"
#include "renderer.h"
#include "fileHelper.h"
#include "SDL.h"
#include "appManager.h"

GameObject **AllGameObjects;
size_t AllGameObjectsSize;

void engineCore_startGameEngine(const char* projectName, int argc, const char* argv[]) {
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
        logger_stop();

        cleanupApp();
        quitApp(1);
    }
    LOG("SDL initialized.");

    // Initialize renderer
    if (renderer_init() == 1) {
        cleanupApp();
        quitApp(1);
    }

    // Start the game loop
    gameLoop_start();

    // Start cleanup after gameLoop ends
    cleanupApp();

    quitApp(0);
}

GameObject* _engineCore_registerGameObject(GameObject go) {
    AllGameObjects = realloc(AllGameObjects, (sizeof(AllGameObjects) + 1) * sizeof(GameObject));

    GameObject* _go = malloc(sizeof(GameObject));
    _go->id = go.id;
    _go->position = go.position;
    _go->properties = go.properties;
    _go->draw = go.draw;

    AllGameObjects[sizeof(AllGameObjects)] = _go;

    return _go;
}