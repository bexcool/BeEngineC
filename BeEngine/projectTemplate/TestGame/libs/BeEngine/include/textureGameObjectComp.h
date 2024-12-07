#ifndef _TEXTUREGAMEOBJECTCOMP_H_
#define _TEXTUREGAMEOBJECTCOMP_H_

#include "SDL.h"
#include "brush.h"
#include "gameObjectComponent.h"

DEFINE_GAMEOBJECTCOMP_START(TextureGameObjectComp);
char imagePath[256];
TextureBrush textureBrush;
DEFINE_GAMEOBJECTCOMP_END(TextureGameObjectComp);

#endif