#include "textureGameObjectComp.h"

#include "SDL.h"
#include "SDL_image.h"
#include "logger.h"
#include "renderer.h"

void _TextureGameObjectComp_registered(TextureGameObjectComp *comp, GameObject *parent) {
    comp->texture = IMG_LoadTexture(gameRenderer, comp->imagePath);
}

void _TextureGameObjectComp_draw(TextureGameObjectComp *comp, GameObject *parent) {
    SDL_Rect drawRect = {comp->worldLocation.x + comp->relativeLocation.x, comp->worldLocation.y + comp->relativeLocation.y, comp->size.x, comp->size.y};
    SDL_RenderCopy(gameRenderer, comp->texture, NULL, &drawRect);
}

void _TextureGameObjectComp_tick(TextureGameObjectComp *comp, GameObject *parent) {}

void _TextureGameObjectComp_destroyed(TextureGameObjectComp *comp, GameObject *parent) {}