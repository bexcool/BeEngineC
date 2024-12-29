#pragma once

#include <stdio.h>

#include "cameraGameObjectComp.h"
#include "gameObject.h"
#include "uiCanvas.h"
#include "vector2.h"

typedef struct Level {
    size_t id;
    char* name;
    // All objects in the level
    GameObjectList allGameObjects;
    UICanvasList allUICanvases;
    // Functions
    void (*event_loaded)();
} Level;

#define DEFINE_LEVEL(name) \
    Level name;            \
    void _##name##_loaded();

#define DECLARE_LEVEL

GameObject* level_spawnGameObject(GameObjectConstructor* gameObjectToSpawn, Vector2* location);
UICanvas* level_createUICanvas();
int level_destroyGameObject(GameObject* gameObject);
int level_destroyGameObjectByID(size_t id);
void level_focusCamera(CameraGameObjectComp* camera, Vector2* bounds);