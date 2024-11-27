#include "physicsGameObjectComp.h"

#include "engineCore.h"
#include "level.h"
#include "logger.h"

void _PhysicsGameObjectComp_tick(PhysicsGameObjectComp *comp, GameObject *parent) {
    Level *l = getLevel();
    GameObject *checkGo;

    // Warn and continue if static game object has a velocity
    if (parent->objectType == STATIC) {
        if (parent->velocity.x != 0 || parent->velocity.y != 0) {
            LOG_W("Physics component: Game object with ID %d is static but has a non-zero velocity!", parent->id);
            return;
        }
    }

    // Calculate new position
    // TODO: Add new position for goCheck
    Vector2 newPosition = VECTOR2(
        parent->velocity.x * getDeltaTime(),
        parent->velocity.y * getDeltaTime() * -1);

    if (parent->objectType != STATIC) {
        // Apply velocity
        parent->position.x += newPosition.x;
        parent->position.y += newPosition.y;
    }

    // Continue if game object does not have collisions
    if (parent->collisionType == NO_COLLISION)
        return;

    // Calculate collisions
    for (size_t j = 0; j < l->allGameObjects.size; j++) {
        checkGo = l->allGameObjects.items[j];

        // Do not check collision on itself or on no-collision object
        if (checkGo->id == parent->id || checkGo->collisionType == NO_COLLISION)
            continue;

        SDL_Rect checkGoRect = {
            .x = checkGo->position.x,
            .y = checkGo->position.y,
            .w = checkGo->size.x,
            .h = checkGo->size.y};

        // Left and right side
        SDL_Rect goRect = {
            .x = parent->position.x,
            .y = parent->position.y,
            .w = parent->size.x,
            .h = parent->size.y};

        // Do not check velocity collision for static object
        if (parent->objectType != STATIC) {
            goRect.y = parent->position.y - newPosition.y;

            if (SDL_HasIntersection(&goRect, &checkGoRect)) {
                if (checkGo->collisionType == BLOCK) {
                    if (parent->velocity.x > 0)
                        parent->position.x = checkGo->position.x - parent->size.x;
                    if (parent->velocity.x < 0)
                        parent->position.x = checkGo->position.x + checkGo->size.x;
                }
            }

            // Top and bottom side
            goRect.x = parent->position.x - newPosition.x;
            goRect.y = parent->position.y;

            if (SDL_HasIntersection(&goRect, &checkGoRect)) {
                if (checkGo->collisionType == BLOCK) {
                    if (parent->velocity.y > 0)
                        parent->position.y = checkGo->position.y + checkGo->size.y;
                    if (parent->velocity.y < 0)
                        parent->position.y = checkGo->position.y - parent->size.y;
                }
            }

            // Reset rectangle values for overlap calculations
            goRect.x = parent->position.x;
            goRect.y = parent->position.y;
        }

        // Check overlap
        if (SDL_HasIntersection(&goRect, &checkGoRect)) {
            if (!ARRAY_CONTAINS(parent->overlappedGameObjects, GameObject *, ->id, checkGo->id)) {
                ARRAY_ADD(parent->overlappedGameObjects, GameObject *, checkGo);
                if (parent->event_beginOverlap != NULL)
                    parent->event_beginOverlap(parent, checkGo);
            }
        } else {
            if (ARRAY_CONTAINS(parent->overlappedGameObjects, GameObject *, ->id, checkGo->id)) {
                size_t index = ARRAY_FIND_INDEX(parent->overlappedGameObjects, GameObject *, ->id, checkGo->id);
                ARRAY_REMOVE(parent->overlappedGameObjects, GameObject *, index);
                if (parent->event_endOverlap != NULL)
                    parent->event_endOverlap(parent, checkGo);
            }
        }
    }
}