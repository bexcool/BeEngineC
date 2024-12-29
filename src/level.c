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
        .event_endOverlap = gameObjectToSpawn->event_endOverlap};

    return _engineCore_registerGameObject(&go);
}

int level_destroyGameObject(GameObject* gameObject) {
    return _engineCore_unregisterGameObject(gameObject->id);
}

int level_destroyGameObjectByID(size_t id) {
    return _engineCore_unregisterGameObject(id);
}

// UI Canvas
UICanvas* level_createUICanvas() {
    return _engineCore_registerUICanvas();
}

int level_destroyUICanvas(UICanvas* canvas) {
    return _engineCore_unregisterUICanvas(canvas->id);
}

int level_destroyUICanvasByID(size_t id) {
    return _engineCore_unregisterUICanvas(id);
}

// Camera
void level_focusCamera(CameraGameObjectComp* camera, Vector2* bounds) {
    if (bounds == NULL)
        camera->_viewportBounds = VECTOR2(-1, -1);
    else
        camera->_viewportBounds = *bounds;
    getRenderer()->focusedCamera = camera;
}