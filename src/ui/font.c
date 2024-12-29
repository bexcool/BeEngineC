#include "font.h"

#include "SDL_ttf.h"
#include "engineCore.h"
#include "logger.h"
#include "string.h"

TTF_Font* font_load(const char* path, const unsigned int size) {
    for (int i = 0; i < getRenderer()->loadedTtfFonts.size; i++) {
        TTF_FontCache* fc = &getRenderer()->loadedTtfFonts.items[i];

        if (strcmp(fc->path, path) == 0) {
            int index;
            if ((index = LIST_FIND_INDEX(fc->sizes, int, , size)) != -1) {
                return fc->fonts.items[index];
            } else {
                TTF_Font* font = TTF_OpenFont(path, size);

                LIST_ADD(fc->fonts, TTF_Font*, font);
                LIST_ADD(fc->sizes, int, size);

                LOG("Font: Cached a new size \"%d\" for font \"%s\".", size, path);

                return font;
            }

            break;
        }
    }

    TTF_FontCache fc;

    // Copy path to the font cache
    strcpy(fc.path, path);

    TTF_Font* font = TTF_OpenFont(path, size);

    LIST_INIT(fc.fonts);
    LIST_INIT(fc.sizes);

    LIST_ADD(fc.fonts, TTF_Font*, font);
    LIST_ADD(fc.sizes, int, size);

    // Add font cache to the render
    LIST_ADD(getRenderer()->loadedTtfFonts, TTF_FontCache, fc);

    LOG("Font: Cached a new font \"%s\" with size \"%d\".", path, size);

    return font;
}

void font_cleanup() {
    for (int i = 0; i < getRenderer()->loadedTtfFonts.size; i++) {
        TTF_FontCache* fc = &getRenderer()->loadedTtfFonts.items[i];

        for (int j = 0; j < fc->fonts.size; j++) {
            TTF_CloseFont(fc->fonts.items[j]);
        }

        LIST_CLEAN(fc->fonts);
        LIST_CLEAN(fc->sizes);
    }

    LIST_CLEAN(getRenderer()->loadedTtfFonts);
}