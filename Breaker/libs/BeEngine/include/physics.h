#ifndef _PHYSICS_H_
#define _PHYSICS_H_

typedef enum CollisionType {
    NO_COLLISION = 0, BLOCK, OVERLAP
} CollisionType;

typedef enum ObjectType {
    STATIC = 0, MOVABLE
} ObjectType;

#endif