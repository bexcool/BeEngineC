#include "testLevel.h"

#include "BeEngine.h"

GameObject *go1, *go2, *go3, *go4, *go5;
const Level testLevel = {.id = 1, .name = "testLevel", .event_loaded = &_testLevel_loaded};

void _testLevel_loaded() {
    go1 = REG_GAMEOBJECT(&GAMEOBJECT(VECTOR2(49.5, 20), VECTOR2(50, 100)));
    go1->event_draw = &drawTest;
    go1->collisionType = COLLISION_OVERLAP;
    go2 = REG_GAMEOBJECT(&GAMEOBJECT(VECTOR2(50, 50), VECTOR2(200, 200)));
    go2->event_draw = &drawTest;
}

void drawTest(GameObject* gameObject) {
    renderer_drawFillRectangle(&COLOR(0, 255, 0), &go1->location, &go1->size);
    renderer_drawFillRectangle(&COLOR(255, 255, 0), &go2->location, &go2->size);
}