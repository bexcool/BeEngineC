#ifndef _BUTTONUICOMPONENT_H_
#define _BUTTONUICOMPONENT_H_

#include "SDL.h"
#include "color.h"
#include "uiCanvas.h"
#include "uiComponent.h"

typedef struct ButtonStyle {
    Color normalColor;
    SDL_Texture *normalTexture;
    Color hoveredColor;
    SDL_Texture *hoveredTexture;
    Color pressedColor;
    SDL_Texture *pressedTexture;
    Color disabledColor;
    SDL_Texture *disabledTexture;
} ButtonStyle;

DEFINE_UICOMPONENT_START(ButtonUIComponent);
ButtonStyle style;
DEFINE_UICOMPONENT_END(ButtonUIComponent);

#endif
