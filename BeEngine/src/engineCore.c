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
#include "level.h"

EngineCore _engineCore;
Level _currentLevel;

void engineCore_startGameEngine(EngineOptions options, int argc, const char* argv[], void (*gameEngineInitialized)()) {
    logger_init(strcat(getParentDirectoryPath(argv[0]), "/log.txt"));

    #ifdef DEBUG
        LOG("Running engine in DEBUG configuration.");
    #endif

    #ifdef NDEBUG
        LOG("Running engine in RELEASE configuration.");
    #endif

    LOG("Starting application...");

    LOG("Initializing engine core...");
    _engineCore_initialize(options);
    LOG("Engine core initialized.");

    LOG("Initializing SDL...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG_E("Could not initialize SDL: %s\n", SDL_GetError());
        logger_stop();

        cleanupApp();
        quitApp(1);
    }
    LOG("SDL initialized.");

    // Initialize renderer
    if (renderer_init(options.projectName) == 1) {
        cleanupApp();
        quitApp(1);
    }

    // Call initialized function
    gameEngineInitialized();

    // Start the game loop
    gameLoop_start();

    // Start cleanup after gameLoop ends
    cleanupApp();

    quitApp(0);
}

void _engineCore_initialize(EngineOptions _options) {
    getCore()->options = _options;
}

void _engineCore_clean() {
    // Clean allGameObjects array
    for (size_t i = 0; i < getLevel()->allGameObjectsSize; i++) {
        free(getLevel()->allGameObjects[i]);
        getLevel()->allGameObjects[i] = NULL;
    }
}

EngineCore* getCore() {
    return &_engineCore;
}

Level* getLevel() {
    return &_currentLevel;
}

int loadLevel(Level *level) {
    return 0;
}

GameObject* _engineCore_registerGameObject(GameObject go) {
    getLevel()->allGameObjects = realloc(getLevel()->allGameObjects, ++(getLevel()->allGameObjectsSize) * sizeof(GameObject));

    GameObject *_go = (GameObject*)malloc(sizeof(GameObject));
    _go->id = go.id;
    _go->position = go.position;
    _go->properties = go.properties;
    _go->draw = go.draw;

    getLevel()->allGameObjects[getLevel()->allGameObjectsSize - 1] = _go;

    return _go;
}