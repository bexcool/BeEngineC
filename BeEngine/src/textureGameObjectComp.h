#ifndef _TEXTUREGAMEOBJECTCOMP_H_
#define _TEXTUREGAMEOBJECTCOMP_H_

#include "SDL.h"
#include "gameObjectComponent.h"

DEFINE_GAMEOBJECTCOMP_START(TextureGameObjectComp);
char imagePath[256];
SDL_Texture *texture;
DEFINE_GAMEOBJECTCOMP_END(TextureGameObjectComp);

#endif