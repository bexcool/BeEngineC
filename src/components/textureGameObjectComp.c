#include "textureGameObjectComp.h"

#include "SDL.h"
#include "SDL_image.h"
#include "color.h"
#include "engineCore.h"
#include "logger.h"
#include "renderer.h"

void _TextureGameObjectComp_registered(TextureGameObjectComp *comp, GameObject *parent) {
    comp->textureBrush._SDL_Texture = IMG_LoadTexture(getRenderer()->gameRenderer, comp->textureBrush.texturePath);
}

void _TextureGameObjectComp_draw(TextureGameObjectComp *comp, GameObject *parent) {
    SDL_Rect drawRect = {comp->worldLocation.x + comp->relativeLocation.x, comp->worldLocation.y + comp->relativeLocation.y, comp->size.x, comp->size.y};

    renderer_rectAdjustByCamera(&drawRect);

    if (!color_equal(&COLOR(255, 255, 255), &comp->textureBrush.color)) {
        SDL_SetTextureColorMod(comp->textureBrush._SDL_Texture, comp->textureBrush.color.r, comp->textureBrush.color.g, comp->textureBrush.color.b);
    }

    SDL_RenderCopy(getRenderer()->gameRenderer, comp->textureBrush._SDL_Texture, NULL, &drawRect);
}

void _TextureGameObjectComp_tick(TextureGameObjectComp *comp, GameObject *parent) {}

void _TextureGameObjectComp_destroyed(TextureGameObjectComp *comp, GameObject *parent) {}

void textureGameObjectComp_changeTexture(TextureGameObjectComp *comp, char *texturePath) {
    if (comp->textureBrush._SDL_Texture) {
        SDL_DestroyTexture(comp->textureBrush._SDL_Texture);
    }

    comp->textureBrush.texturePath = texturePath;
    comp->textureBrush._SDL_Texture = IMG_LoadTexture(getRenderer()->gameRenderer, texturePath);
}