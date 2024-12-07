#include "level.h"

#include "engineCore.h"

GameObject* level_spawnGameObject(GameObjectSpawn* gameObjectToSpawn, Vector2* location) {
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