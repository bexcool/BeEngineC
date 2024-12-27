#include "cameraGameObjectComp.h"

#include "engineCore.h"
#include "renderer.h"

void _CameraGameObjectComp_registered(CameraGameObjectComp *comp, GameObject *parent) {
}

void _CameraGameObjectComp_tick(CameraGameObjectComp *comp, GameObject *parent) {
    if (getRenderer()->focusedCamera == comp) {
        SDL_Rect viewport;
        SDL_RenderGetViewport(getRenderer()->gameRenderer, &viewport);

        comp->_viewportWorldLocation =
            VECTOR2(comp->worldLocation.x - viewport.w / 2,
                    comp->worldLocation.y - viewport.h / 2);

        if (comp->_viewportBounds.w != -1) {
            SDL_Rect *bounds = &comp->_viewportBounds;

            if (comp->worldLocation.x - viewport.w / 2 < bounds->x) {
                comp->_viewportWorldLocation.x = bounds->x;
            } else if (comp->worldLocation.x + viewport.w / 2 > bounds->x + bounds->w) {
                comp->_viewportWorldLocation.x = bounds->x + bounds->w - viewport.w;
            }

            if (comp->worldLocation.y - viewport.h / 2 < bounds->y) {
                comp->_viewportWorldLocation.y = bounds->y;
            } else if (comp->worldLocation.y + viewport.h / 2 > bounds->y + bounds->h) {
                comp->_viewportWorldLocation.y = bounds->y + bounds->h - viewport.h;
            }
        }
    }
}

void _CameraGameObjectComp_draw(CameraGameObjectComp *comp, GameObject *parent) {
}

void _CameraGameObjectComp_destroyed(CameraGameObjectComp *comp, GameObject *parent) {
}
