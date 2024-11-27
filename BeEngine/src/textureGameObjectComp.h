#ifndef _TEXTUREGAMEOBJECTCOMP_H_
#define _TEXTUREGAMEOBJECTCOMP_H_

#include "SDL.h"
#include "gameObjectComponent.h"

PREPARE_GAMEOBJECTCOMP_START(TextureGameObjectComp);
char imagePath[256];
SDL_Texture *texture;
PREPARE_GAMEOBJECTCOMP_END(TextureGameObjectComp);

#endif