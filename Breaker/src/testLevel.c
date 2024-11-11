#include "testLevel.h"
#include "BeEngine.h"

GameObject *go1, *go2, *go3, *go4, *go5;

void _testLevel_initialize() {
    go1 = REG_GAMEOBJECT(&GAMEOBJECT(0, VECTOR2(20, 20), NULL, &drawTest));
    go2 = REG_GAMEOBJECT(&GAMEOBJECT(0, VECTOR2(100, 20), NULL, &drawTest));
    go3 = REG_GAMEOBJECT(&GAMEOBJECT(0, VECTOR2(250, 200), NULL, &drawTest));
    go4 = REG_GAMEOBJECT(&GAMEOBJECT(0, VECTOR2(0, 0), NULL, &drawTest));
    go5 = REG_GAMEOBJECT(&GAMEOBJECT(0, VECTOR2(400, 100), NULL, &drawTest));
}

void drawTest(GameObject* gameObject) {
    renderer_fillRectangle(&COLOR(0, 255, 0), &go1->position, &VECTOR2(50, 100));
    renderer_fillRectangle(&COLOR(100, 100, 0), &go2->position, &VECTOR2(100, 100));
    renderer_fillRectangle(&COLOR(255, 255, 255), &go3->position, &VECTOR2(200, 10));
    renderer_fillRectangle(&COLOR(100, 50, 100), &go4->position, &VECTOR2(10, 10));
    renderer_fillRectangle(&COLOR(255, 0, 255), &go5->position, &VECTOR2(50, 50));
}