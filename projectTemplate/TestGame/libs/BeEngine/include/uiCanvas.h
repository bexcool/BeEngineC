#pragma once

#include "list.h"
#include "uiComponent.h"
#include "visibility.h"

// Type definitions
DEFINE_LIST(UIComponentList, void *);

typedef struct UICanvas {
    size_t id;
    UIComponentList uiComponents;
    Visibility visibility;
    void (*event_register)(struct UICanvas *);
    void (*event_tick)(struct UICanvas *);
    void (*event_destroyed)(struct UICanvas *);
} UICanvas;

// Macros
#define UICANVAS_ATTACH_COMP(name, component, canvas)      \
    (component)->event_registered = &_##name##_registered; \
    (component)->event_tick = &_##name##_tick;             \
    (component)->event_draw = &_##name##_draw;             \
    (component)->event_destroyed = &_##name##_destroyed;   \
    uiCanvas_attachUIComponent(canvas, component);

void uiCanvas_attachUIComponent(UICanvas *canvas, void *uiComponent);