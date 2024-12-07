#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "limits.h"
#include "list.h"
#include "physics.h"
#include "stdlib.h"
#include "vector2.h"

DEFINE_LIST(GameObjectList, struct GameObject*);
DEFINE_LIST(GameObjectCompList, void*);

typedef struct GameObjectSpawn {
    Vector2 size;
    CollisionType collisionType;
    ObjectType objectType;
    void* properties;
    void (*event_draw)(struct GameObject*);
    void (*event_tick)(struct GameObject*);
    void (*event_destroyed)(struct GameObject*);
    void (*event_beginOverlap)(struct GameObject*, struct GameObject*);  // Self, Collided object
    void (*event_endOverlap)(struct GameObject*, struct GameObject*);    // Self, Collided object
} GameObjectSpawn;

typedef struct GameObject {
    size_t id;
    Vector2 location;
    Vector2 size;
    Vector2 velocity;
    CollisionType collisionType;
    ObjectType objectType;
    struct GameObject* parentGameObject;
    GameObjectList overlappedGameObjects;
    GameObjectCompList components;
    void* properties;
    void (*event_draw)(struct GameObject*);
    void (*event_tick)(struct GameObject*);
    void (*event_destroyed)(struct GameObject*);
    void (*event_beginOverlap)(struct GameObject*, struct GameObject*);  // Self, Collided object
    void (*event_endOverlap)(struct GameObject*, struct GameObject*);    // Self, Collided object
} GameObject;

// Přidat sám sebe do nějakého liste objektů a přidat tam svoji draw funkci

#define DEFINE_GAMEOBJECT(name) \
    void _##name##_draw(GameObject* gameObject);

#define GAMEOBJECT_ATTACH_COMP(gameObject, type, component) \
    (component)->event_registered = &_##type##_registered;  \
    (component)->event_tick = &_##type##_tick;              \
    (component)->event_draw = &_##type##_draw;              \
    (component)->event_destroyed = &_##type##_destroyed;    \
    _gameObject_attachComponent(gameObject, component);

// Private
/**
 * DO NOT USE! Use "GAMEOBJECT_ATTACH_COMP" instead.
 *
 * \param go Game object.
 * \param component Game object component.
 */
int _gameObject_attachComponent(GameObject* go, void* component);

// Public
void gameObject_attackToGameObject(GameObject* go, GameObject* goParent);
void gameObject_setVelocity(GameObject* go, Vector2 velocity);
void gameObject_addVelocity(GameObject* go, Vector2 velocity);

#endif