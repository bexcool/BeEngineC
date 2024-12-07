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