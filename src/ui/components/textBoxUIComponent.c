#include "textBoxUIComponent.h"

#include <math.h>
#include <sys/time.h>

#include "engineCore.h"
#include "logger.h"
#include "string.h"
#include "uiCanvas.h"

void _TextBoxUIComponent_registered(TextBoxUIComponent *comp, UICanvas *canvas) {
    snprintf(comp->displayName, sizeof(comp->displayName), "TextBoxUIComponent_%zu", comp->id);
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
        renderer_UI_drawFillRectangle(&comp->backgroundBrush.color, &comp->_actualPosition, &comp->size);
    } else {
        SDL_Rect rect = vector2x2toSDL_Rect(&comp->_actualPosition, &comp->size);
        SDL_RenderCopy(getRenderer()->gameRenderer, comp->backgroundBrush.texture, NULL, &rect);
    }

    // Border
    if (engineCore_getFocusedUIComponent() == comp) {
        renderer_UI_drawRectangle(&comp->focusedBorderBrush.color, &VECTOR2(comp->_actualPosition.x, comp->_actualPosition.y - comp->focusedBorderBrush.thickness.top / 2.0), &VECTOR2(comp->size.x, comp->focusedBorderBrush.thickness.top));
        renderer_UI_drawRectangle(&comp->focusedBorderBrush.color, &VECTOR2(comp->_actualPosition.x, comp->_actualPosition.y + comp->size.y - comp->focusedBorderBrush.thickness.bottom / 2.0), &VECTOR2(comp->size.x, comp->focusedBorderBrush.thickness.bottom));
        renderer_UI_drawRectangle(&comp->focusedBorderBrush.color, &VECTOR2(comp->_actualPosition.x - comp->focusedBorderBrush.thickness.left / 2.0, comp->_actualPosition.y), &VECTOR2(comp->focusedBorderBrush.thickness.left, comp->size.y));
        renderer_UI_drawRectangle(&comp->focusedBorderBrush.color, &VECTOR2(comp->_actualPosition.x + comp->size.x - comp->focusedBorderBrush.thickness.right / 2.0, comp->_actualPosition.y), &VECTOR2(comp->focusedBorderBrush.thickness.right, comp->size.y));

    } else {
        renderer_UI_drawRectangle(&comp->borderBrush.color, &comp->_actualPosition, &comp->size);
    }

    // Text
    int w, h;
    float actualTextSizeX = comp->size.x - comp->padding.left - comp->padding.right,
          actualTextSizeY = comp->size.y - comp->padding.top - comp->padding.bottom;
    TTF_SizeText(comp->font._ttfFont, comp->text, &w, &h);
    SDL_Rect textRect = {.x = comp->_actualPosition.x + comp->padding.left, .y = comp->_actualPosition.y + comp->padding.top, .w = (w > actualTextSizeX) ? actualTextSizeX : w, .h = (h > actualTextSizeY) ? actualTextSizeY : h};
    SDL_RenderCopy(getRenderer()->gameRenderer, comp->_textTexture, NULL, &textRect);

    // Cursor
    if (engineCore_getFocusedUIComponent() == comp) {
        struct timeval time;
        gettimeofday(&time, NULL);
        Color cursorColor = COLOR_RGBA(comp->font.color.r, comp->font.color.g, comp->font.color.b, (time.tv_sec - comp->_lastTimeTyped.tv_sec >= 1) ? (sin(time.tv_usec / 1000000.0) > 0.5 ? 0 : 255) : 255);
        renderer_UI_drawFillRectangle(&cursorColor, &VECTOR2(comp->_actualPosition.x + w + (h / 15) + comp->padding.left, comp->_actualPosition.y + (h / 10) + comp->padding.top), &VECTOR2(1, h - (h / 10)));
    }
}

void _TextBoxUIComponent_destroyed(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_destroyed) comp->event_destroyed(comp, canvas);
}

void _TextBoxUIComponent_clicked(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_clicked) comp->event_clicked(comp, canvas);
}

void _TextBoxUIComponent_pressed(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_pressed) comp->event_pressed(comp, canvas);
    if (engineCore_getFocusedUIComponent() != comp) {
        gettimeofday(&comp->_lastTimeTyped, NULL);
        engineCore_setFocusedUIComponent(canvas, comp);
    }
}

void _TextBoxUIComponent_released(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_released) comp->event_released(comp, canvas);
}

void _TextBoxUIComponent_hovered(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_hovered) comp->event_hovered(comp, canvas);

    SDL_Cursor *cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    SDL_SetCursor(cursor);
}

void _TextBoxUIComponent_unhovered(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_unhovered) comp->event_unhovered(comp, canvas);

    SDL_Cursor *cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_SetCursor(cursor);
}

void _TextBoxUIComponent_input(TextBoxUIComponent *comp, UICanvas *canvas) {
    if (comp->event_input) comp->event_input(comp, canvas);

    // Get text size
    int w, h;
    TTF_SizeText(comp->font._ttfFont, comp->text, &w, &h);

    SDL_Event *input = getCore()->lastInputEvent;
    // Get ASCII char
    if (input->type == SDL_TEXTINPUT) {
        gettimeofday(&comp->_lastTimeTyped, NULL);

        if (strlen(comp->text) < 255) {
            char tmp[256];

            strcpy(tmp, comp->text);
            strcat(tmp, input->text.text);

            int w, h;
            TTF_SizeText(comp->font._ttfFont, tmp, &w, &h);

            // Ensure text fits in the box
            if (w < comp->size.x - (h / 10) - comp->padding.left - comp->padding.right) {
                strcat(comp->text, input->text.text);
                if (comp->event_textChanged) comp->event_textChanged(comp, canvas);
            }
        }
    } else if (input->type == SDL_KEYDOWN) {
        if (input->key.keysym.sym == SDLK_BACKSPACE) {
            gettimeofday(&comp->_lastTimeTyped, NULL);

            if (strlen(comp->text) > 0) {
                comp->text[strlen(comp->text) - 1] = '\0';

                if (comp->event_textChanged) comp->event_textChanged(comp, canvas);
            }
        }
    }
}