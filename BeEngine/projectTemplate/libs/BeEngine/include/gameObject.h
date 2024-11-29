#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "array.h"
#include "limits.h"
#include "physics.h"
#include "stdlib.h"
#include "vector2.h"

DEFINE_ARRAY(GameObjectArray, struct GameObject*);

typedef struct GameObject {
    size_t id;
    Vector2 position;
    Vector2 size;
    Vector2 velocity;
    CollisionType collisionType;
    ObjectType objectType;
    struct GameObject* parentGameObject;
    GameObjectArray overlappedGameObjects;
    void* properties;
    void (*event_draw)(struct GameObject*);
    void (*event_tick)(struct GameObject*);
    void (*event_destroyed)(struct GameObject*);
    void (*event_beginOverlap)(struct GameObject*, struct GameObject*);  // Self, Collided object
    void (*event_endOverlap)(struct GameObject*, struct GameObject*);    // Self, Collided object
} GameObject;

// Přidat sám sebe do nějakého arraye objektů a přidat tam svoji draw funkci

#define DEFINE_GAMEOBJECT(name) \
    void _##name##_draw(GameObject* gameObject);

#define GAMEOBJECT_ID(_id, _position, _size, _properties, _event_draw) \
    ((GameObject){                                                     \
        .id = _id,                                                     \
        .position = _position,                                         \
        .size = _size,                                                 \
        .properties = _properties,                                     \
        .event_draw = _event_draw,                                     \
        .collisionType = BLOCK,                                        \
        .objectType = STATIC})

#define GAMEOBJECT(_position, _size, _properties, _event_draw) \
    ((GameObject){                                             \
        .id = rand() % SIZE_T_MAX + 1,                         \
        .position = _position,                                 \
        .size = _size,                                         \
        .properties = _properties,                             \
        .event_draw = _event_draw,                             \
        .collisionType = BLOCK,                                \
        .objectType = STATIC})

#endif