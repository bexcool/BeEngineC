#include "gameObject.h"

#include "gameObjectComponent.h"
#include "logger.h"
#include "physicsGameObjectComp.h"

int gameObject_attachComponent(GameObject *go, void *component) {
    ARRAY_ADD(go->components, void *, component);

    void (*event_registered)(void *, GameObject *) = *(void (**)(void *, GameObject *))(component);
    LOG_W("Address: %p", component);
    if (event_registered != NULL) {
        event_registered(component, go);
    }

    return 0;
}