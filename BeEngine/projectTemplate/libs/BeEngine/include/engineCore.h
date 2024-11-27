#ifndef _ENGINECORE_H_
#define _ENGINECORE_H_

#include <SDL2/SDL.h>
#include <stdlib.h>

#include "gameObject.h"
#include "level.h"

// Type definitions
typedef struct EngineOptions {
    const char* projectName;
    unsigned int window_x;
    unsigned int window_y;
    unsigned int window_width;
    unsigned int window_height;
    Level initialLevel;
} EngineOptions;

typedef struct EngineEvents {
    void (*event_engineInitialized)();
    void (*event_anyInput)(SDL_Event*);
} EngineEvents;

typedef struct EngineCore {
    EngineOptions options;
    EngineEvents events;
} EngineCore;

// Macros
#define TRUE 1
#define FALSE 0

#define REG_GAMEOBJECT(gameObject) \
    _engineCore_registerGameObject(gameObject)

#define UNREG_GAMEOBJECT(id) \
    _engineCore_unregisterGameObject(id)

#define NEW_ID rand() % (SIZE_T_MAX + 1)

// Public functions
void engineCore_startGameEngine(EngineOptions* options, EngineEvents* events, int argc, const char* argv[]);
int engineCore_loadLevel(Level* level);

// Getters
EngineCore* getCore();
Level* getLevel();
double getDeltaTime();
GameObject* getFocusedGameObject();

// Private functions
void _engineCore_initialize(EngineOptions* _options, EngineEvents* _events);
void _engineCore_clean();
void _engineCore_cleanGameObjects();

void _engineCore_tick();

GameObject* _engineCore_registerGameObject(GameObject* go);
int _engineCore_unregisterGameObject(int id);

#endif