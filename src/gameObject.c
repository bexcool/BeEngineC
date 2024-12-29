#include "gameObject.h"

#include "gameObjectComponent.h"
#include "logger.h"
#include "physicsGameObjectComp.h"

int _gameObject_attachComponent(GameObject *go, void *component) {
    LIST_ADD(go->components, void *, component);

    // Set random ID
    size_t *id = (size_t *)((char *)component + (sizeof(void (*)(void *, GameObject *)) * GAMEOBJECTCOMP_EVENT_COUNT));
    (*id) = rand() % SIZE_T_MAX + 1;

    void (*event_registered)(void *, GameObject *) = *(void (**)(void *, GameObject *))(component);
    if (event_registered != NULL) {
        event_registered(component, go);
    }

    return 0;
}

void gameObject_attachToGameObject(GameObject *go, GameObject *goParent) {
    go->parentGameObject = goParent;
    go->relativeLocation = VECTOR2(go->location.x - goParent->location.x, go->location.y - goParent->location.y);
}

void gameObject_setVelocity(GameObject *go, Vector2 *velocity) {
    if (go->objectType != OBJECT_MOVABLE) {
        LOG_W("Game object: Cannot set velocity to a non-movable game object (ID: %d).", go->id);
        return;
    }

    if (go->parentGameObject != NULL) {
        LOG_W("Game object: Cannot set velocity to a child game object (ID: %d).", go->id);
        return;
    }

    go->velocity = *velocity;
}

void gameObject_addVelocity(GameObject *go, Vector2 *velocity) {
    if (go->objectType != OBJECT_MOVABLE) {
        LOG_W("Game object: Cannot add velocity to a non-movable game object (ID: %d).", go->id);
        return;
    }

    if (go->parentGameObject != NULL) {
        LOG_W("Game object: Cannot add velocity to a child game object (ID: %d).", go->id);
        return;
    }

    vector2_add(&go->velocity, velocity);
}