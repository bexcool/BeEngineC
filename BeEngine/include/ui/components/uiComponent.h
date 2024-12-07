#pragma once

#include "vector2.h"
#include "visibility.h"

#define UICOMPONENT_EVENT_COUNT 9

/*  void*, UICanvas* event_registered
    event_tick
    event_draw
    event_destroyed
    event_clicked
    event_pressed
    event_released
    event_hovered
    event_unhovered
    size_t id
    Vector2 position
    Vector2 size
    Visibility visibility
    int isPressed
    int isHovered
    int disabled
*/
#define DEFINE_UICOMPONENT_START(name)                       \
    typedef struct name {                                    \
        void (*event_registered)(struct name *, UICanvas *); \
        void (*event_tick)(struct name *, UICanvas *);       \
        void (*event_draw)(struct name *, UICanvas *);       \
        void (*event_destroyed)(struct name *, UICanvas *);  \
        void (*event_clicked)(struct name *, UICanvas *);    \
        void (*event_pressed)(struct name *, UICanvas *);    \
        void (*event_released)(struct name *, UICanvas *);   \
        void (*event_hovered)(struct name *, UICanvas *);    \
        void (*event_unhovered)(struct name *, UICanvas *);  \
        size_t id;                                           \
        Vector2 position;                                    \
        Vector2 size;                                        \
        Visibility visibility;                               \
        int isPressed;                                       \
        int isHovered;                                       \
        int disabled;

#define DEFINE_UICOMPONENT_END(name)                                \
    }                                                               \
    name;                                                           \
                                                                    \
    void _##name##_registered(struct name *comp, UICanvas *canvas); \
    void _##name##_tick(struct name *comp, UICanvas *canvas);       \
    void _##name##_draw(struct name *comp, UICanvas *canvas);       \
    void _##name##_destroyed(struct name *comp, UICanvas *canvas);  \
    void _##name##_clicked(struct name *comp, UICanvas *canvas);    \
    void _##name##_pressed(struct name *comp, UICanvas *canvas);    \
    void _##name##_released(struct name *comp, UICanvas *canvas);   \
    void _##name##_hovered(struct name *comp, UICanvas *canvas);    \
    void _##name##_unhovered(struct name *comp, UICanvas *canvas);