#include "buttonUIComponent.h"

#include "engineCore.h"
#include "logger.h"
#include "renderer.h"
#include "uiCanvas.h"
#include "vector2.h"

void _ButtonUIComponent_registered(ButtonUIComponent *comp, UICanvas *canvas) {
    snprintf(comp->displayName, sizeof(comp->displayName), "ButtonUIComponent_%zu", comp->id);
    if (comp->event_registered) comp->event_registered(comp, canvas);
}

void _ButtonUIComponent_tick(ButtonUIComponent *comp, UICanvas *canvas) {
}

void _ButtonUIComponent_draw(ButtonUIComponent *comp, UICanvas *canvas) {
    // Return if not visible
    if (comp->visibility != VISIBILITY_VISIBLE) return;

    // Get renderer
    Renderer *r = getRenderer();

    // Disabled
    if (comp->disabled) {
        if (comp->style.disabledBrush._SDL_Texture == NULL) {
            renderer_UI_drawFillRectangle(&comp->style.disabledBrush.color, &comp->_actualPosition, &comp->size);
            return;
        }

        SDL_Rect rect = vector2x2toSDL_Rect(&comp->_actualPosition, &comp->size);
        SDL_RenderCopy(r->gameRenderer, comp->style.disabledBrush._SDL_Texture, NULL, &rect);
        return;
    }

    // Pressed
    if (comp->isPressed) {
        if (comp->style.presssedBrush._SDL_Texture == NULL) {
            renderer_UI_drawFillRectangle(&comp->style.presssedBrush.color, &comp->_actualPosition, &comp->size);
            return;
        }

        SDL_Rect rect = vector2x2toSDL_Rect(&comp->_actualPosition, &comp->size);
        SDL_RenderCopy(r->gameRenderer, comp->style.presssedBrush._SDL_Texture, NULL, &rect);
        return;
    }

    // Hovered
    if (comp->isHovered) {
        if (comp->style.hoveredBrush._SDL_Texture == NULL) {
            renderer_UI_drawFillRectangle(&comp->style.hoveredBrush.color, &comp->_actualPosition, &comp->size);
            return;
        }

        SDL_Rect rect = vector2x2toSDL_Rect(&comp->_actualPosition, &comp->size);
        SDL_RenderCopy(r->gameRenderer, comp->style.hoveredBrush._SDL_Texture, NULL, &rect);
        return;
    }

    // Normal
    if (comp->style.normalBrush._SDL_Texture == NULL) {
        renderer_UI_drawFillRectangle(&comp->style.normalBrush.color, &comp->_actualPosition, &comp->size);
        return;
    }

    SDL_Rect rect = vector2x2toSDL_Rect(&comp->_actualPosition, &comp->size);
    SDL_RenderCopy(r->gameRenderer, comp->style.normalBrush._SDL_Texture, NULL, &rect);
}

void _ButtonUIComponent_destroyed(ButtonUIComponent *comp, UICanvas *canvas) {
    if (comp->event_destroyed) comp->event_destroyed(comp, canvas);
}

void _ButtonUIComponent_clicked(ButtonUIComponent *comp, UICanvas *canvas) {
    if (comp->event_clicked) comp->event_clicked(comp, canvas);
}

void _ButtonUIComponent_pressed(ButtonUIComponent *comp, UICanvas *canvas) {
    if (comp->event_pressed) comp->event_pressed(comp, canvas);
    engineCore_setFocusedUIComponent(canvas, comp);
}

void _ButtonUIComponent_released(ButtonUIComponent *comp, UICanvas *canvas) {
    if (comp->event_released) comp->event_released(comp, canvas);
}

void _ButtonUIComponent_hovered(ButtonUIComponent *comp, UICanvas *canvas) {
    if (comp->event_hovered) comp->event_hovered(comp, canvas);
}

void _ButtonUIComponent_unhovered(ButtonUIComponent *comp, UICanvas *canvas) {
    if (comp->event_unhovered) comp->event_unhovered(comp, canvas);
}

void _ButtonUIComponent_input(ButtonUIComponent *comp, UICanvas *canvas) {
    if (comp->event_input) comp->event_input(comp, canvas);
}
