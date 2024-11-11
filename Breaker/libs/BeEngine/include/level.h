#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <stdio.h>
#include "gameObject.h"
#include "array.h"

PREPARE_ARRAY(GameObjectArray, GameObject*);

typedef struct Level {
    size_t id;
    char *name;
    // Game objects
    GameObjectArray allGameObjects;
    // Functions
    void (*initialize)();
} Level;

#define PREPARE_LEVEL(name) \
    void _##name##_initialize();

#endif