#include "testLevel.h"
#include "BeEngine.h"

GameObject *go1;

void _testLevel_initialize() {
    go1 = REG_GAMEOBJECT(GAMEOBJECT(0, VECTOR2(20, 20), NULL, &drawTest));
}

void drawTest(GameObject* gameObject) {
    renderer_fillRectangle(COLOR(0, 255, 0), go1->position, VECTOR2(100, 100));
}