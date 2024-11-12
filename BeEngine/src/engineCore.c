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

void engineCore_startGameEngine(EngineOptions *options, EngineEvents *events, int argc, const char* argv[]) {
    logger_init(strcat(getParentDirectoryPath(argv[0]), "/log.txt"));

    #ifdef DEBUG
        LOG("Running engine in DEBUG configuration.");
    #endif

    #ifdef NDEBUG
        LOG("Running engine in RELEASE configuration.");
    #endif

    LOG("Starting application...");

    LOG("Initializing engine core...");
    _engineCore_initialize(options, events);
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
    if (renderer_init(options->projectName) == 1) {
        cleanupApp();
        quitApp(1);
    }

    // Call initialized function
    if (getCore()->events.engineInitialized != NULL)
        getCore()->events.engineInitialized();

    // Start the game loop
    gameLoop_start();

    // Start cleanup after gameLoop ends
    cleanupApp();

    quitApp(0);
}

void _engineCore_initialize(EngineOptions *_options, EngineEvents *_events) {
    getCore()->options = *_options;
    getCore()->events = *_events;

    loadLevel(&getCore()->options.initialLevel);
}

void _engineCore_clean() {
    _engineCore_cleanGameObjects();
}

void _engineCore_cleanGameObjects() {
    // Clean allGameObjects array
    for (size_t i = 0; i < getLevel()->allGameObjects.size; i++) {
        free(getLevel()->allGameObjects.items[i]);
        getLevel()->allGameObjects.items[i] = NULL;
    }

    ARRAY_CLEAN(getLevel()->allGameObjects);
}

EngineCore* getCore() {
    return &_engineCore;
}

Level* getLevel() {
    return &_currentLevel;
}

int loadLevel(Level *level) {
    LOG("Requested to load level \"%s\".", level->name);

    if (level->name == NULL) {
        LOG_E("Failed to load level! Level name is NULL.");
        cleanupApp();
        exit(1);
    }

    // Check ID
    if (level->id == 0) {
        LOG_W("Level does not have an ID. This could cause issues in the future.");
    }

    // Check loaded
    if (level->loaded == NULL) {
        LOG_W("Level does not have a pointer to the \"loaded\" function. This could cause issues in the future.");
    }

    LOG("Cleaning game objects in the current level.");
    _engineCore_cleanGameObjects();

    LOG("Transitioning from \"%s\" to \"%s\"...", getLevel()->name, level->name);
    _currentLevel = *level;

    LOG("Initializing new level...");
    ARRAY_INIT(getLevel()->allGameObjects);
    LOG("Level initialized.");

    LOG("Level \"%s\" loaded successfully.", getLevel()->name);
    if(getLevel()->loaded != NULL) getLevel()->loaded();

    return 1;
}

// Relloc nevolat furt
GameObject* _engineCore_registerGameObject(GameObject *go) {
    GameObject *_go = (GameObject*)malloc(sizeof(GameObject));
    _go->id = go->id;
    _go->position = go->position;
    _go->properties = go->properties;
    _go->draw = go->draw;

    ARRAY_ADD(getLevel()->allGameObjects, GameObject*, _go);

    return _go;
}