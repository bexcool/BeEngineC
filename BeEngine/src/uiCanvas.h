#ifndef _UICANVAS_H_
#define _UICANVAS_H_

#include "array.h"
#include "uiComponent.h"
#include "visibility.h"

// Type definitions
DEFINE_ARRAY(UIComponentArray, void *);

typedef struct UICanvas {
    size_t id;
    UIComponentArray uiComponents;
    Visibility visibility;
    void (*event_register)(struct UICanvas *);
    void (*event_tick)(struct UICanvas *);
    void (*event_destroyed)(struct UICanvas *);
} UICanvas;

// Macros
#define UICANVAS_ID(_id, _position, _size, _event_draw) \
    ((UICanvas){                                        \
        .id = _id,                                      \
        .position = _position})

void uiCanvas_attachUIComponent(UICanvas *canvas, void *uiComponent);

#endif