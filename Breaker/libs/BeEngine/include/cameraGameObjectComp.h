#pragma once

#include "SDL.h"
#include "gameObjectComponent.h"

DEFINE_GAMEOBJECTCOMP_START(CameraGameObjectComp);
SDL_Rect _viewportBounds;
Vector2 _viewportWorldLocation;
DEFINE_GAMEOBJECTCOMP_END(CameraGameObjectComp);