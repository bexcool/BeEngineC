#ifndef _UICOMPONENT_H_
#define _UICOMPONENT_H_

#include "vector2.h"
#include "visibility.h"

#define UICOMPONENT_EVENT_COUNT 4

/*  event_registered
    event_tick
    event_draw
    event_destroyed
    event_clicked
    event_pressed
    event_released
    event_hovered
    event_unhovered
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

#define ATTACHs_UICOMPONENT(name, component, canvas)       \
    (component)->event_registered = &_##name##_registered; \
    (component)->event_tick = &_##name##_tick;             \
    (component)->event_draw = &_##name##_draw;             \
    (component)->event_destroyed = &_##name##_destroyed;   \
    (component)->event_clicked = &_##name##_clicked;       \
    (component)->event_pressed = &_##name##_pressed;       \
    (component)->event_released = &_##name##_released;     \
    (component)->event_hovered = &_##name##_hovered;       \
    (component)->event_unhovered = &_##name##_unhovered;   \
    uiCanvas_attachComponent(parent, component);

#endif