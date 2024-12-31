#include "physicsGameObjectComp.h"

#include "engineCore.h"
#include "level.h"
#include "list.h"
#include "logger.h"

void _PhysicsGameObjectComp_tick(PhysicsGameObjectComp *comp, GameObject *parent) {
    Level *l = getLevel();
    GameObject *checkGo;

    // Warn and continue if static game object has a velocity
    if (parent->objectType == OBJECT_STATIC) {
        if (parent->velocity.x != 0 || parent->velocity.y != 0) {
            LOG_W("Physics component: Game object with ID %d is static but has a non-zero velocity!", parent->id);
            return;
        }
    }

    // Calculate new location
    // TODO: Add new location for goCheck
    Vector2 newlocation = VECTOR2(
        parent->velocity.x * getDeltaTime(),
        parent->velocity.y * getDeltaTime() * -1);

    if (parent->objectType != OBJECT_STATIC) {
        // Apply velocity
        parent->location.x += newlocation.x;
        parent->location.y += newlocation.y;
    }

    // Continue if game object does not have collisions
    if (parent->collisionType == COLLISION_NO_COLLISION)
        return;

    // Calculate collisions
    for (size_t j = 0; j < l->allGameObjects.size; j++) {
        checkGo = l->allGameObjects.items[j];

        // Do not check collision on itself or on no-collision object
        if (checkGo->id == parent->id || checkGo->collisionType == COLLISION_NO_COLLISION)
            continue;

        SDL_Rect checkGoRect = {
            .x = checkGo->location.x,
            .y = checkGo->location.y,
            .w = checkGo->size.x,
            .h = checkGo->size.y};

        // Left and right side
        SDL_Rect goRect = {
            .x = parent->location.x,
            .y = parent->location.y,
            .w = parent->size.x,
            .h = parent->size.y};

        // Do not check velocity collision for static object
        if (parent->objectType != OBJECT_STATIC && parent->collisionType == COLLISION_BLOCK) {
            goRect.y = parent->location.y - newlocation.y;

            if (SDL_HasIntersection(&goRect, &checkGoRect)) {
                if (checkGo->collisionType == COLLISION_BLOCK) {
                    if (parent->velocity.x > 0) {
                        parent->location.x = checkGo->location.x - parent->size.x;
                        if (parent->event_hit) parent->event_hit(parent, checkGo, &VECTOR2(1, 0));
                    }
                    if (parent->velocity.x < 0) {
                        parent->location.x = checkGo->location.x + checkGo->size.x;
                        if (parent->event_hit) parent->event_hit(parent, checkGo, &VECTOR2(-1, 0));
                    }
                }
            }

            // Top and bottom side
            goRect.x = parent->location.x - newlocation.x;
            goRect.y = parent->location.y;

            if (SDL_HasIntersection(&goRect, &checkGoRect)) {
                if (checkGo->collisionType == COLLISION_BLOCK) {
                    if (parent->velocity.y > 0) {
                        parent->location.y = checkGo->location.y + checkGo->size.y;
                        if (parent->event_hit) parent->event_hit(parent, checkGo, &VECTOR2(0, 1));
                    }
                    if (parent->velocity.y < 0) {
                        parent->location.y = checkGo->location.y - parent->size.y;
                        if (parent->event_hit) parent->event_hit(parent, checkGo, &VECTOR2(0, -1));
                    }
                }
            }

            // Reset rectangle values for overlap calculations
            goRect.x = parent->location.x;
            goRect.y = parent->location.y;
        }

        // Check overlap
        if (SDL_HasIntersection(&goRect, &checkGoRect)) {
            if (!LIST_CONTAINS(parent->overlappedGameObjects, GameObject *, ->id, checkGo->id)) {
                LIST_ADD(parent->overlappedGameObjects, GameObject *, checkGo);
                if (parent->event_beginOverlap != NULL)
                    parent->event_beginOverlap(parent, checkGo);
            }
        } else {
            size_t index = LIST_FIND_INDEX(parent->overlappedGameObjects, GameObject *, ->id, checkGo->id);
            if (index != -1) {
                LIST_REMOVE(parent->overlappedGameObjects, GameObject *, index);
                if (parent->event_endOverlap != NULL)
                    parent->event_endOverlap(parent, checkGo);
            }
        }
    }
}

void _PhysicsGameObjectComp_registered(PhysicsGameObjectComp *comp, GameObject *parent) {}
void _PhysicsGameObjectComp_draw(PhysicsGameObjectComp *comp, GameObject *parent) {}
void _PhysicsGameObjectComp_destroyed(PhysicsGameObjectComp *comp, GameObject *parent) {}