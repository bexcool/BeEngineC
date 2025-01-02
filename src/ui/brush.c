#include "brush.h"

TextureBrush newTextureBrush(Color *color, char *texturePath) {
    return (TextureBrush){.color = *color, .texturePath = texturePath};
}

Thickness newThickness1(const unsigned int amount) {
    return (Thickness){amount, amount, amount, amount};
}

Thickness newThickness4(const unsigned int left, const unsigned int top, const unsigned int right, const unsigned int bottom) {
    return (Thickness){left, top, right, bottom};
}