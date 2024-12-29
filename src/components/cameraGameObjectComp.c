#include "cameraGameObjectComp.h"

#include "engineCore.h"
#include "logger.h"
#include "renderer.h"

void _CameraGameObjectComp_registered(CameraGameObjectComp *comp, GameObject *parent) {
}

void _CameraGameObjectComp_tick(CameraGameObjectComp *comp, GameObject *parent) {
    if (getRenderer()->focusedCamera == comp) {
        SDL_Rect viewport;
        SDL_RenderGetViewport(getRenderer()->gameRenderer, &viewport);

        if (comp->_viewportBounds.x != -1) {
            Vector2 *bounds = &comp->_viewportBounds;

            if (comp->_viewportBounds.x > viewport.w && comp->worldLocation.x - viewport.w / 2 > 0) {
                if (comp->worldLocation.x + viewport.w / 2 < bounds->x) {
                    comp->_viewportWorldLocation.x = comp->worldLocation.x - viewport.w / 2;
                } else if (comp->worldLocation.x + viewport.w / 2 > bounds->x) {
                    comp->_viewportWorldLocation.x = bounds->x - viewport.w;
                }
            } else {
                comp->_viewportWorldLocation.x = 0;
            }

            if (comp->_viewportBounds.y > viewport.h && comp->worldLocation.y - viewport.h / 2 > 0) {
                if (comp->worldLocation.y + viewport.h / 2 < bounds->y) {
                    comp->_viewportWorldLocation.y = comp->worldLocation.y - viewport.h / 2;
                } else if (comp->worldLocation.y + viewport.h / 2 > bounds->y) {
                    comp->_viewportWorldLocation.y = bounds->y - viewport.h;
                }
            } else {
                comp->_viewportWorldLocation.y = 0;
            }
        } else {
            comp->_viewportWorldLocation =
                VECTOR2(comp->worldLocation.x - viewport.w / 2,
                        comp->worldLocation.y - viewport.h / 2);
        }
    }
}

void _CameraGameObjectComp_draw(CameraGameObjectComp *comp, GameObject *parent) {
}

void _CameraGameObjectComp_destroyed(CameraGameObjectComp *comp, GameObject *parent) {
}
