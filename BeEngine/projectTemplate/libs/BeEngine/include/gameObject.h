#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "vector2.h"

typedef struct GameObject {
    size_t id;
    Vector2 position;
    void* properties;
    void (*draw)(struct GameObject*);
} GameObject;

// Přidat sám sebe do nějakého arraye objektů a přidat tam svoji draw funkci

#define PREPARE_GAMEOBJECT(name) \
    void _##name##_draw(GameObject* gameObject);

#define GAMEOBJECT(_id, _position, _properties, _draw) \
    ((GameObject) { .id = _id, .position = _position, .properties = _properties, .draw = _draw })

#endif