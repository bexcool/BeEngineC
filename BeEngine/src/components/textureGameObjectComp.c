#include "textureGameObjectComp.h"

#include "SDL.h"
#include "SDL_image.h"
#include "color.h"
#include "engineCore.h"
#include "logger.h"

void _TextureGameObjectComp_registered(TextureGameObjectComp *comp, GameObject *parent) {
    comp->textureBrush.texture = IMG_LoadTexture(getRenderer()->gameRenderer, comp->imagePath);
}

void _TextureGameObjectComp_draw(TextureGameObjectComp *comp, GameObject *parent) {
    SDL_Rect drawRect = {comp->worldLocation.x + comp->relativeLocation.x, comp->worldLocation.y + comp->relativeLocation.y, comp->size.x, comp->size.y};

    if (color_equal(&COLOR(255, 255, 255), &comp->textureBrush.color)) {
        SDL_SetTextureColorMod(comp->textureBrush.texture, comp->textureBrush.color.r, comp->textureBrush.color.g, comp->textureBrush.color.b);
    }

    SDL_RenderCopy(getRenderer()->gameRenderer, comp->textureBrush.texture, NULL, &drawRect);
}

void _TextureGameObjectComp_tick(TextureGameObjectComp *comp, GameObject *parent) {}

void _TextureGameObjectComp_destroyed(TextureGameObjectComp *comp, GameObject *parent) {}