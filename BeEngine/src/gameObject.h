#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "array.h"
#include "limits.h"
#include "physics.h"
#include "stdlib.h"
#include "vector2.h"

DEFINE_ARRAY(GameObjectArray, struct GameObject*);
DEFINE_ARRAY(GameObjectCompArray, void*);

typedef struct GameObject {
    size_t id;
    Vector2 location;
    Vector2 size;
    Vector2 velocity;
    CollisionType collisionType;
    ObjectType objectType;
    struct GameObject* parentGameObject;
    GameObjectArray overlappedGameObjects;
    GameObjectCompArray components;
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

#define GAMEOBJECT_ID(_id, _location, _size, _properties, _event_draw) \
    ((GameObject){                                                     \
        .id = _id,                                                     \
        .location = _location,                                         \
        .size = _size,                                                 \
        .properties = _properties,                                     \
        .collisionType = BLOCK,                                        \
        .objectType = STATIC})

#define GAMEOBJECT(_location, _size, _properties, _event_draw) \
    ((GameObject){                                             \
        .id = rand() % SIZE_T_MAX + 1,                         \
        .location = _location,                                 \
        .size = _size,                                         \
        .properties = _properties,                             \
        .collisionType = BLOCK,                                \
        .objectType = STATIC})

#define GAMEOBJECT_ATTACH_COMPONENT(componentType, component) \
    ARRAY_ADD(go->components, componentType*, &component);

int gameObject_attachComponent(GameObject* go, void* component);

#endif