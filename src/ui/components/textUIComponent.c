#include "textUIComponent.h"

#include "color.h"
#include "engineCore.h"
#include "font.h"
#include "logger.h"
#include "uiCanvas.h"

char lastText[256];
int lastSize;

void _TextUIComponent_registered(TextUIComponent *comp, UICanvas *canvas) {
    snprintf(comp->displayName, sizeof(comp->displayName), "TextUIComponent_%zu", comp->id);
    if (comp->event_registered) comp->event_registered(comp, canvas);

    comp->font._ttfFont = font_load(comp->font.path, comp->font.size);

    comp->_textSurface = TTF_RenderText_Solid(comp->font._ttfFont, comp->text, color_toSDL_Color(&comp->font.color));
    comp->_textTexture = SDL_CreateTextureFromSurface(getRenderer()->gameRenderer, comp->_textSurface);

    strcpy(lastText, comp->text);
    lastSize = comp->font.size;
}

void _TextUIComponent_tick(TextUIComponent *comp, UICanvas *canvas) {
    if (lastSize != comp->font.size) {
        comp->font._ttfFont = font_load(comp->font.path, comp->font.size);
    }

    if (strcmp(lastText, comp->text) != 0 || lastSize != comp->font.size) {
        SDL_FreeSurface(comp->_textSurface);
        SDL_DestroyTexture(comp->_textTexture);
        comp->_textSurface = TTF_RenderText_Solid(comp->font._ttfFont, comp->text, color_toSDL_Color(&comp->font.color));
        comp->_textTexture = SDL_CreateTextureFromSurface(getRenderer()->gameRenderer, comp->_textSurface);

        strcpy(lastText, comp->text);
        lastSize = comp->font.size;
    }
}

void _TextUIComponent_draw(TextUIComponent *comp, UICanvas *canvas) {
    SDL_Rect textRect = {.x = comp->_actualPosition.x, .y = comp->_actualPosition.y, .w = comp->_textSurface->w, .h = comp->_textSurface->h};
    // TTF_SizeText(font, "put your text here", &textRect.w, &textRect.h);
    SDL_RenderCopy(getRenderer()->gameRenderer, comp->_textTexture, NULL, &textRect);
}

void _TextUIComponent_destroyed(TextUIComponent *comp, UICanvas *canvas) {
}

void _TextUIComponent_clicked(TextUIComponent *comp, UICanvas *canvas) {
}

void _TextUIComponent_pressed(TextUIComponent *comp, UICanvas *canvas) {
}

void _TextUIComponent_released(TextUIComponent *comp, UICanvas *canvas) {
}

void _TextUIComponent_hovered(TextUIComponent *comp, UICanvas *canvas) {
}

void _TextUIComponent_unhovered(TextUIComponent *comp, UICanvas *canvas) {
}

void _TextUIComponent_input(TextUIComponent *comp, UICanvas *canvas) {
}