#ifndef _ENGINECORE_H_
#define _ENGINECORE_H_

#include <stdlib.h>
#include "gameObject.h"
#include "level.h"

typedef struct EngineCore {

} EngineCore;

// Macros
#define REG_GAMEOBJECT(gameObject) \
    _engineCore_registerGameObject(gameObject)

#define UNREG_GAMEOBJECT(id) \
    _engineCore_registerGameObject(id)

// Public functions
void engineCore_startGameEngine(const char* projectName, int argc, const char* argv[], void (*gameEngineInitialized)());
EngineCore* getCore();
Level* getLevel();
int loadLevel(Level *level);

// Private functions
void _engineCore_initialize();
void _engineCore_clean();
GameObject* _engineCore_registerGameObject(GameObject go);
int _engineCore_unregisterGameObject(int id);

#endif