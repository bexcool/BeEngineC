#include "borderUIComponent.h"

#include "engineCore.h"
#include "renderer.h"
#include "uiCanvas.h"

void _BorderUIComponent_registered(BorderUIComponent *comp, UICanvas *canvas) {
}

void _BorderUIComponent_tick(BorderUIComponent *comp, UICanvas *canvas) {
}

void _BorderUIComponent_draw(BorderUIComponent *comp, UICanvas *canvas) {
    if (comp->fillBrush.texture == NULL) {
        renderer_drawFillRectangle(&comp->fillBrush.color, &comp->position, &comp->size);
    } else {
        SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
        SDL_RenderCopy(getRenderer()->gameRenderer, comp->fillBrush.texture, NULL, &rect);
    }

    // Border
    renderer_drawRectangle(&comp->borderBrush.color, &comp->position, &comp->size);
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