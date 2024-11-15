#include "testLevel.h"

#include "BeEngine.h"

GameObject *go1, *go2, *go3, *go4, *go5;
const Level testLevel = {.id = 2, .name = "testLevel", .event_loaded = &_testLevel_loaded};

void _testLevel_loaded() {
    go1 = REG_GAMEOBJECT(&GAMEOBJECT(0, VECTOR2(49.5, 20), VECTOR2(50, 100), NULL, &drawTest));
    go1->collisionType = OVERLAP;
    go2 = REG_GAMEOBJECT(&GAMEOBJECT(1, VECTOR2(50, 50), VECTOR2(200, 200), NULL, &drawTest));
}

void drawTest(GameObject* gameObject) {
    renderer_fillRectangle(&COLOR(0, 255, 0), &go1->position, &go1->size);
    renderer_fillRectangle(&COLOR(255, 255, 0), &go2->position, &go2->size);
}