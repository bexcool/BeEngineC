#include "buttonUIComponent.h"

#include "engineCore.h"
#include "logger.h"
#include "renderer.h"
#include "uiCanvas.h"
#include "vector2.h"

void _ButtonUIComponent_registered(ButtonUIComponent *comp, UICanvas *canvas) {
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
        if (comp->style.disabledBrush.texture == NULL) {
            renderer_drawFillRectangle(&comp->style.disabledBrush.color, &comp->position, &comp->size);
            return;
        }

        SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
        SDL_RenderCopy(r->gameRenderer, comp->style.disabledBrush.texture, NULL, &rect);
        return;
    }

    // Pressed
    if (comp->isPressed) {
        if (comp->style.presssedBrush.texture == NULL) {
            renderer_drawFillRectangle(&comp->style.presssedBrush.color, &comp->position, &comp->size);
            return;
        }

        SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
        SDL_RenderCopy(r->gameRenderer, comp->style.presssedBrush.texture, NULL, &rect);
        return;
    }

    // Hovered
    if (comp->isHovered) {
        if (comp->style.hoveredBrush.texture == NULL) {
            renderer_drawFillRectangle(&comp->style.hoveredBrush.color, &comp->position, &comp->size);
            return;
        }

        SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
        SDL_RenderCopy(r->gameRenderer, comp->style.hoveredBrush.texture, NULL, &rect);
        return;
    }

    // Normal
    if (comp->style.normalBrush.texture == NULL) {
        renderer_drawFillRectangle(&comp->style.normalBrush.color, &comp->position, &comp->size);
        return;
    }

    SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
    SDL_RenderCopy(r->gameRenderer, comp->style.normalBrush.texture, NULL, &rect);
}

void _ButtonUIComponent_destroyed(ButtonUIComponent *comp, UICanvas *canvas) {
}

void _ButtonUIComponent_clicked(ButtonUIComponent *comp, UICanvas *canvas) {
}

void _ButtonUIComponent_pressed(ButtonUIComponent *comp, UICanvas *canvas) {
}

void _ButtonUIComponent_released(ButtonUIComponent *comp, UICanvas *canvas) {
}

void _ButtonUIComponent_hovered(ButtonUIComponent *comp, UICanvas *canvas) {
}

void _ButtonUIComponent_unhovered(ButtonUIComponent *comp, UICanvas *canvas) {
}
