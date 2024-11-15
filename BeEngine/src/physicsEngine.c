#include "physicsEngine.h"

#include "engineCore.h"
#include "gameObject.h"
#include "logger.h"
#include "physics.h"

void _physicsEngine_tick() {
    Level* l = getLevel();

    for (size_t i = 0; i < l->allGameObjects.size; i++) {
        GameObject *go = l->allGameObjects.items[i], *checkGo;

        // Warn and continue if static game object has a velocity
        if (go->objectType == STATIC) {
            if (go->velocity.x != 0 || go->velocity.y != 0) {
                LOG_W("Physics engine: Game object with ID %d is static but has a non-zero velocity!", go->id);
                continue;
            }
        }

        // Calculate new position
        // TODO: Add new position for goCheck
        Vector2 newPosition = VECTOR2(
            go->velocity.x * getDeltaTime(),
            go->velocity.y * getDeltaTime() * -1);

        if (go->objectType != STATIC) {
            // Apply velocity
            go->position.x += newPosition.x;
            go->position.y += newPosition.y;
        }

        // Continue if game object does not have collisions
        if (go->collisionType == NO_COLLISION)
            continue;

        // Calculate collisions
        for (size_t j = 0; j < l->allGameObjects.size; j++) {
            checkGo = l->allGameObjects.items[j];

            // Do not check collision on itself or on no-collision object
            if (checkGo->id == go->id || checkGo->collisionType == NO_COLLISION)
                continue;

            SDL_Rect checkGoRect = {
                .x = checkGo->position.x,
                .y = checkGo->position.y,
                .w = checkGo->size.x,
                .h = checkGo->size.y};

            // Left and right side
            SDL_Rect goRect = {
                .x = go->position.x,
                .y = go->position.y,
                .w = go->size.x,
                .h = go->size.y};

            // Do not check velocity collision for static object
            if (go->objectType != STATIC) {
                goRect.y = go->position.y - newPosition.y;

                if (SDL_HasIntersection(&goRect, &checkGoRect)) {
                    if (checkGo->collisionType == BLOCK) {
                        if (go->velocity.x > 0)
                            go->position.x = checkGo->position.x - go->size.x;
                        if (go->velocity.x < 0)
                            go->position.x = checkGo->position.x + checkGo->size.x;
                    }
                }

                // Top and bottom side
                goRect.x = go->position.x - newPosition.x;
                goRect.y = go->position.y;

                if (SDL_HasIntersection(&goRect, &checkGoRect)) {
                    if (checkGo->collisionType == BLOCK) {
                        if (go->velocity.y > 0)
                            go->position.y = checkGo->position.y + checkGo->size.y;
                        if (go->velocity.y < 0)
                            go->position.y = checkGo->position.y - go->size.y;
                    }
                }

                // Reset rectangle values for overlap calculations
                goRect.x = go->position.x;
                goRect.y = go->position.y;
            }

            // Check overlap
            if (SDL_HasIntersection(&goRect, &checkGoRect)) {
                if (!ARRAY_CONTAINS(go->overlappedGameObjects, GameObject*, ->id, checkGo->id)) {
                    ARRAY_ADD(go->overlappedGameObjects, GameObject*, checkGo);
                    if (go->event_beginOverlap != NULL)
                        go->event_beginOverlap(go, checkGo);
                }
            } else {
                if (ARRAY_CONTAINS(go->overlappedGameObjects, GameObject*, ->id, checkGo->id)) {
                    size_t index = ARRAY_FIND_INDEX(go->overlappedGameObjects, GameObject*, ->id, checkGo->id);
                    ARRAY_REMOVE(go->overlappedGameObjects, GameObject*, index);
                    if (go->event_endOverlap != NULL)
                        go->event_endOverlap(go, checkGo);
                }
            }
        }
    }
}

int physicsEngine_doesGameObjectCollide(GameObject* go) {
    // Calculate new position
    Vector2 newPosition = VECTOR2(
        go->velocity.x * getDeltaTime(),
        go->velocity.x * getDeltaTime());

    return FALSE;
}