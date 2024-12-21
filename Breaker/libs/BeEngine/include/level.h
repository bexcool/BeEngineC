#pragma once

#include <stdio.h>

#include "gameObject.h"
#include "vector2.h"

typedef struct Level {
    size_t id;
    char* name;
    // Game objects
    GameObjectList allGameObjects;
    // Functions
    void (*event_loaded)();
} Level;

#define DEFINE_LEVEL(name) \
    Level name;            \
    void _##name##_loaded();

#define DECLARE_LEVEL

GameObject* level_spawnGameObject(GameObjectSpawn* gameObjectToSpawn, Vector2* location);
int level_destroyGameObject(GameObject* gameObject);