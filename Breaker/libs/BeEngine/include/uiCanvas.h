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
#define UICANVAS_ID(_id, _position) \
    ((UICanvas){                    \
        .id = _id,                  \
        .position = _position})

void uiCanvas_attachUIComponent(UICanvas *canvas, void *uiComponent);