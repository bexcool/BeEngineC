#ifndef _ENGINECORE_H_
#define _ENGINECORE_H_

#include <stdlib.h>
#include "gameObject.h"
#include "level.h"
#include "SDL.h"

// Type definitions
typedef struct EngineOptions {
    const char* projectName;
    unsigned int window_x;
    unsigned int window_y;
    unsigned int window_width;
    unsigned int window_height;
} EngineOptions;

typedef struct EngineEvents {
    void (*engineInitialized)();
    void (*inputEvent)(SDL_Event);
} EngineEvents;

typedef struct EngineCore {
    EngineOptions options;
    EngineEvents events;
} EngineCore;

// Macros
#define REG_GAMEOBJECT(gameObject) \
    _engineCore_registerGameObject(gameObject)

#define UNREG_GAMEOBJECT(id) \
    _engineCore_registerGameObject(id)

// Public functions
void engineCore_startGameEngine(EngineOptions options, EngineEvents events, int argc, const char* argv[]);
EngineCore* getCore();
Level* getLevel();
int loadLevel(Level *level);

// Private functions
void _engineCore_initialize(EngineOptions _options, EngineEvents _events);
void _engineCore_clean();
GameObject* _engineCore_registerGameObject(GameObject go);
int _engineCore_unregisterGameObject(int id);

#endif