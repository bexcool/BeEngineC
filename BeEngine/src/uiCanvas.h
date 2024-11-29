#ifndef _UICANVAS_H_
#define _UICANVAS_H_

#include "BeEngineUI.h"
#include "array.h"

DEFINE_ARRAY(UIComponentArray, void*);

typedef struct UICanvas {
    UIComponentArray uiComponents;
    Visibility visibility;
} UICanvas;

#endif