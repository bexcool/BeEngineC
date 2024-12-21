#include "textBoxUIComponent.h"

#include "engineCore.h"
#include "logger.h"
#include "string.h"
#include "uiCanvas.h"

void _TextBoxUIComponent_registered(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_registered) comp->event_registered(comp, canvas);

    comp->font._ttfFont = font_load(comp->font.path, comp->font.size);

    comp->_textSurface = TTF_RenderText_Solid(comp->font._ttfFont, comp->text, color_toSDL_Color(&comp->font.color));
    comp->_textTexture = SDL_CreateTextureFromSurface(getRenderer()->gameRenderer, comp->_textSurface);

    strcpy(comp->_lastText, comp->text);
    comp->_lastSize = comp->font.size;
}

void _TextBoxUIComponent_tick(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_tick) comp->event_tick(comp, canvas);

    if (comp->_lastSize != comp->font.size) {
        comp->font._ttfFont = font_load(comp->font.path, comp->font.size);
    }

    if (strcmp(comp->_lastText, comp->text) != 0 || comp->_lastSize != comp->font.size) {
        LOG_W("Text: %s", comp->text);
        LOG_W("Last text: %s", comp->_lastText);
        SDL_FreeSurface(comp->_textSurface);
        SDL_DestroyTexture(comp->_textTexture);
        comp->_textSurface = TTF_RenderText_Solid(comp->font._ttfFont, comp->text, color_toSDL_Color(&comp->font.color));
        comp->_textTexture = SDL_CreateTextureFromSurface(getRenderer()->gameRenderer, comp->_textSurface);

        strcpy(comp->_lastText, comp->text);
        comp->_lastSize = comp->font.size;
    }
}

void _TextBoxUIComponent_draw(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_draw) comp->event_draw(comp, canvas);

    if (comp->backgroundBrush.texture == NULL) {
        renderer_drawFillRectangle(&comp->backgroundBrush.color, &comp->position, &comp->size);
    } else {
        SDL_Rect rect = vector2x2toSDL_Rect(&comp->position, &comp->size);
        SDL_RenderCopy(getRenderer()->gameRenderer, comp->backgroundBrush.texture, NULL, &rect);
    }

    // Border
    if (engineCore_getFocusedUIComponent() == comp) {
        renderer_drawRectangle(&comp->focusedBorderBrush.color, &VECTOR2(comp->position.x, comp->position.y - comp->focusedBorderBrush.thickness.top / 2.0), &VECTOR2(comp->size.x, comp->focusedBorderBrush.thickness.top));
        renderer_drawRectangle(&comp->focusedBorderBrush.color, &VECTOR2(comp->position.x, comp->position.y + comp->size.y - comp->focusedBorderBrush.thickness.bottom / 2.0), &VECTOR2(comp->size.x, comp->focusedBorderBrush.thickness.bottom));
        renderer_drawRectangle(&comp->focusedBorderBrush.color, &VECTOR2(comp->position.x - comp->focusedBorderBrush.thickness.left / 2.0, comp->position.y), &VECTOR2(comp->focusedBorderBrush.thickness.left, comp->size.y));
        renderer_drawRectangle(&comp->focusedBorderBrush.color, &VECTOR2(comp->position.x + comp->size.x - comp->focusedBorderBrush.thickness.right / 2.0, comp->position.y), &VECTOR2(comp->focusedBorderBrush.thickness.right, comp->size.y));

    } else {
        renderer_drawRectangle(&comp->borderBrush.color, &comp->position, &comp->size);
    }

    // Text
    int w, h;
    TTF_SizeText(comp->font._ttfFont, comp->text, &w, &h);
    SDL_Rect textRect = {.x = comp->position.x, .y = comp->position.y, .w = w, .h = h};
    SDL_RenderCopy(getRenderer()->gameRenderer, comp->_textTexture, NULL, &textRect);
}

void _TextBoxUIComponent_destroyed(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_destroyed) comp->event_destroyed(comp, canvas);
}

void _TextBoxUIComponent_clicked(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_clicked) comp->event_clicked(comp, canvas);
}

void _TextBoxUIComponent_pressed(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_pressed) comp->event_pressed(comp, canvas);
    engineCore_setFocusedUIComponent(canvas, comp);
}

void _TextBoxUIComponent_released(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_released) comp->event_released(comp, canvas);
}

void _TextBoxUIComponent_hovered(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_hovered) comp->event_hovered(comp, canvas);
}

void _TextBoxUIComponent_unhovered(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_unhovered) comp->event_unhovered(comp, canvas);
}

void _TextBoxUIComponent_input(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_input) comp->event_input(comp, canvas);

    SDL_Event *input = getCore()->lastInputEvent;
    // Get ASCII char
    if (input->type == SDL_TEXTINPUT) {
        if (strlen(comp->text) < 255) {
            strcat(comp->text, input->text.text);

            if (comp->event_textChanged) comp->event_textChanged(comp, canvas);
        }
    } else if (input->type == SDL_KEYDOWN) {
        if (input->key.keysym.sym == SDLK_BACKSPACE) {
            if (strlen(comp->text) > 0) {
                comp->text[strlen(comp->text) - 1] = '\0';

                if (comp->event_textChanged) comp->event_textChanged(comp, canvas);
            }
        }
    }
}