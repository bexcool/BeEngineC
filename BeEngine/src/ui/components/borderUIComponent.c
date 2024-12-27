#include "borderUIComponent.h"

#include "constraint.h"
#include "engineCore.h"
#include "renderer.h"
#include "uiCanvas.h"

void _BorderUIComponent_registered(BorderUIComponent *comp, UICanvas *canvas) {
    snprintf(comp->displayName, sizeof(comp->displayName), "BorderUIComponent_%zu", comp->id);
    if (comp->event_registered) comp->event_registered(comp, canvas);
}

void _BorderUIComponent_tick(BorderUIComponent *comp, UICanvas *canvas) {
}

void _BorderUIComponent_draw(BorderUIComponent *comp, UICanvas *canvas) {
    if (comp->fillBrush.texture == NULL) {
        renderer_UI_drawFillRectangle(&comp->fillBrush.color, &comp->_actualPosition, &comp->size);
    } else {
        SDL_Rect rect = vector2x2toSDL_Rect(&comp->_actualPosition, &comp->size);
        SDL_RenderCopy(getRenderer()->gameRenderer, comp->fillBrush.texture, NULL, &rect);
    }

    // Border
    renderer_UI_drawRectangle(&comp->borderBrush.color, &comp->_actualPosition, &comp->size);
}

void _BorderUIComponent_destroyed(BorderUIComponent *comp, UICanvas *canvas) {
}

void _BorderUIComponent_clicked(BorderUIComponent *comp, UICanvas *canvas) {
}

void _BorderUIComponent_pressed(BorderUIComponent *comp, UICanvas *canvas) {
}

void _BorderUIComponent_released(BorderUIComponent *comp, UICanvas *canvas) {
}

void _BorderUIComponent_hovered(BorderUIComponent *comp, UICanvas *canvas) {
}

void _BorderUIComponent_unhovered(BorderUIComponent *comp, UICanvas *canvas) {
}

void _BorderUIComponent_input(BorderUIComponent *comp, UICanvas *canvas) {
}