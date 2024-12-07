#include "brush.h"

TextureBrush newTextureBrush(const Color *color, SDL_Texture *texture) {
    return (TextureBrush){(*color), texture};
}

Thickness newThickness1(const unsigned int amount) {
    return (Thickness){amount, amount, amount, amount};
}

Thickness newThickness4(const unsigned int left, const unsigned int top, const unsigned int right, const unsigned int bottom) {
    return (Thickness){left, top, right, bottom};
}