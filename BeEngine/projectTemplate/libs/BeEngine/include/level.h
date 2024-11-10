#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <stdio.h>
#include "gameObject.h"

typedef struct Level {
    size_t id;
    char *name;
    // Game objects
    GameObject **allGameObjects;
    size_t allGameObjectsSize;
    // Functions
    void (*initialize)();
} Level;

#define PREPARE_LEVEL(name) \
    void _##name##_initialize();

#endif