#ifndef _ENGINECORE_H_
#define _ENGINECORE_H_

#include <stdlib.h>
#include "gameObject.h"

// Macros
#define REG_GAMEOBJECT(gameObject) \
    _engineCore_registerGameObject(gameObject)

#define UNREG_GAMEOBJECT(id) \
    _engineCore_registerGameObject(id)

// Variables
extern GameObject **AllGameObjects;

// Public functions
void engineCore_startGameEngine(const char* projectName, int argc, const char* argv[]);

// Private functions
GameObject* _engineCore_registerGameObject(GameObject go);
int _engineCore_unregisterGameObject(int id);

#endif