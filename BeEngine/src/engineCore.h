#ifndef _ENGINECORE_H_
#define _ENGINECORE_H_

#include <stdlib.h>
#include "gameObject.h"

#define REG_GAMEOBJECT(gameObject) \
    _engineCore_registerGameObject(gameObject)

#define UNREG_GAMEOBJECT(id) \
    _engineCore_registerGameObject(id)

extern GameObject **AllGameObjects;
extern size_t AllGameObjectsSize;

void engineCore_startGameEngine(const char* projectName, int argc, const char* argv[]);

GameObject* _engineCore_registerGameObject(GameObject go);
int _engineCore_unregisterGameObject(int id);

#endif