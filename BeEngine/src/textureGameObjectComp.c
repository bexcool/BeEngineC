#include "textureGameObjectComp.h"

#include "SDL.h"
#include "SDL_image.h"
#include "logger.h"
#include "renderer.h"

void _TextureGameObjectComp_registered(TextureGameObjectComp *comp, GameObject *go) {
    comp->texture = IMG_LoadTexture(gameRenderer, comp->imagePath);
    LOG("Texture registered!");
}

void _TextureGameObjectComp_draw(TextureGameObjectComp *comp, GameObject *go) {
    SDL_Rect drawRect = {comp->worldLocation.x + comp->relativeLocation.x, comp->worldLocation.y + comp->relativeLocation.y, comp->size.x, comp->size.y};
    SDL_RenderCopy(gameRenderer, comp->texture, NULL, &drawRect);
}