#include "ButtonUIComponent.h"

#include "renderer.h"
#include "uiCanvas.h"
#include "vector2.h"

void _ButtonUIComponent_registered(ButtonUIComponent *comp, UICanvas *canvas) {
}

void _ButtonUIComponent_tick(ButtonUIComponent *comp, UICanvas *canvas) {
}

void _ButtonUIComponent_draw(ButtonUIComponent *comp, UICanvas *canvas) {
    // Disabled
    if (comp->disabled) {
        if (comp->style.disabledTexture == NULL) {
            renderer_drawFillRectangle(&comp->style.disabledColor, &comp->position, &comp->size);
            return;
        }

        SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
        SDL_RenderCopy(gameRenderer, comp->style.disabledTexture, NULL, &rect);
        return;
    }

    // Pressed
    if (comp->isPressed) {
        if (comp->style.pressedTexture == NULL) {
            renderer_drawFillRectangle(&comp->style.pressedColor, &comp->position, &comp->size);
            return;
        }

        SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
        SDL_RenderCopy(gameRenderer, comp->style.pressedTexture, NULL, &rect);
        return;
    }

    // Hovered
    if (comp->isHovered) {
        if (comp->style.hoveredTexture == NULL) {
            renderer_drawFillRectangle(&comp->style.hoveredColor, &comp->position, &comp->size);
            return;
        }

        SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
        SDL_RenderCopy(gameRenderer, comp->style.hoveredTexture, NULL, &rect);
        return;
    }

    // Normal
    if (comp->style.normalTexture == NULL) {
        renderer_drawFillRectangle(&comp->style.normalColor, &comp->position, &comp->size);
        return;
    }

    SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
    SDL_RenderCopy(gameRenderer, comp->style.normalTexture, NULL, &rect);
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
