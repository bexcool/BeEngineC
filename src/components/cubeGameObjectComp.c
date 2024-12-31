#include "cubeGameObjectComp.h"

#include "engineCore.h"
#include "renderer.h"

void _CubeGameObjectComp_registered(CubeGameObjectComp *comp, GameObject *parent) {
}

void _CubeGameObjectComp_tick(CubeGameObjectComp *comp, GameObject *parent) {
}

void _CubeGameObjectComp_draw(CubeGameObjectComp *comp, GameObject *parent) {
    renderer_drawFillRectangle(&comp->color, &comp->worldLocation, &comp->size);
}

void _CubeGameObjectComp_destroyed(CubeGameObjectComp *comp, GameObject *parent) {
}
