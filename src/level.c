#include "level.h"

#include "engineCore.h"
#include "uiCanvas.h"

// Game Object
GameObject* level_spawnGameObject(GameObjectConstructor* gameObjectToSpawn, Vector2* location) {
    GameObject go = {
        .id = rand() % SIZE_T_MAX + 1,
        .location = (*location),
        .size = gameObjectToSpawn->size,
        .collisionType = gameObjectToSpawn->collisionType,
        .objectType = gameObjectToSpawn->objectType,
        .properties = gameObjectToSpawn->properties,
        .event_draw = gameObjectToSpawn->event_draw,
        .event_tick = gameObjectToSpawn->event_tick,
        .event_destroyed = gameObjectToSpawn->event_destroyed,
        .event_beginOverlap = gameObjectToSpawn->event_beginOverlap,
        .event_endOverlap = gameObjectToSpawn->event_endOverlap,
        .event_hit = gameObjectToSpawn->event_hit};

    return _engineCore_registerGameObject(&go);
}

void level_destroyGameObject(GameObject* gameObject) {
    _engineCore_unregisterGameObject(gameObject);
}

// UI Canvas
UICanvas* level_createUICanvas() {
    return _engineCore_registerUICanvas();
}

void level_destroyUICanvas(UICanvas* canvas) {
    _engineCore_unregisterUICanvas(canvas);
}

// Camera
void level_focusCamera(CameraGameObjectComp* camera, Vector2* bounds) {
    if (bounds == NULL)
        camera->_viewportBounds = VECTOR2(-1, -1);
    else
        camera->_viewportBounds = *bounds;
    getRenderer()->focusedCamera = camera;
}