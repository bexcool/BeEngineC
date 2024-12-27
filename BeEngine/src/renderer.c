#include "renderer.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "appManager.h"
#include "color.h"
#include "engineCore.h"
#include "font.h"
#include "gameObject.h"
#include "list.h"
#include "logger.h"
#include "vector2.h"

SDL_Surface *statsTextSurface;
SDL_Texture *statsTextTexture;
TTF_Font *debugFont;

#ifndef NDEBUG

int debugShowStats = 0, debugShowCollisions = 0;

#endif

int renderer_init() {
    LOG("Initializing renderer...");

    EngineOptions opt = getCore()->options;
    Renderer *r = getRenderer();

    LOG("Renderer: Creating SDL window...");
    r->gameWindow = SDL_CreateWindow(
        opt.projectName,
        opt.window_x,
        opt.window_y,
        opt.window_width,
        opt.window_height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (r->gameWindow == NULL) {
        LOG_E("Renderer: Could not create window: %s\n", SDL_GetError());
        return -1;
    }
    LOG("Renderer: SDL window created.");

    LOG("Renderer: Creating SDL renderer...");
    // Set OpenGL as the rendering driver
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    r->gameRenderer = SDL_CreateRenderer(
        r->gameWindow,
        -1,
        SDL_RENDERER_ACCELERATED);  //| SDL_RENDERER_PRESENTVSYNC);

    if (r->gameRenderer == NULL) {
        LOG_E("Renderer: Could not create renderer: %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetRenderDrawBlendMode(r->gameRenderer, SDL_BLENDMODE_BLEND);

    LOG("Renderer: SDL renderer created.");

    LOG("Renderer: Initializing SDL_image...");
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        LOG_E("Renderer: Could not initialize SDL_image: %s", IMG_GetError());
        return -1;
    }
    LOG("Renderer: SDL_image initialized.");

    LOG("Renderer: Initializing SDL_ttf...");
    if (TTF_Init() == -1) {
        LOG_E("Renderer: Could not initialize SDL_ttf: %s", TTF_GetError());
        return -1;
    }
    LOG("Renderer: SDL_ttf initialized.");

    debugFont = font_load("./assets/fonts/AvrileSansUI-Regular.ttf", 24);

    LOG("Renderer initialized.");

    return 0;
}

void renderer_render() {
    Renderer *r = getRenderer();

    if (getCore()->_loadingLevel) return;

    static size_t frame = 0;
    SDL_SetRenderDrawColor(r->gameRenderer, 0, 0, 0, 255);
    SDL_RenderClear(r->gameRenderer);

    Level *l = getLevel();

    for (size_t i = 0; i < l->allGameObjects.size; i++) {
        GameObject *go = l->allGameObjects.items[i];

        if (go->event_draw != NULL)
            go->event_draw(l->allGameObjects.items[i]);

        for (size_t j = 0; j < go->components.size; j++) {
            void *comp = go->components.items[j];

            void (*comp_event_draw)(void *, GameObject *) = *(void (**)(void *, GameObject *))(comp + (sizeof(void (*)(void *, GameObject *)) * 2));
            if (comp_event_draw != NULL)
                comp_event_draw(comp, go);
        }

#ifndef NDEBUG

        if (debugShowCollisions && go->collisionType != COLLISION_NO_COLLISION) {
            renderer_drawRectangle(&COLOR(255, 0, 0), &VECTOR2(go->location.x, go->location.y), &VECTOR2(go->size.x, go->size.y));
            SDL_RenderDrawLine(r->gameRenderer, go->location.x, go->location.y, go->location.x + go->size.x - 1, go->location.y + go->size.y - 1);
            SDL_RenderDrawLine(r->gameRenderer, go->location.x, go->location.y + go->size.y - 1, go->location.x + go->size.x - 1, go->location.y);
        }

#endif
    }

    for (int i = 0; i < getCore()->allUICanvases.size; i++) {
        UICanvas *canvas = getCore()->allUICanvases.items[i];

        for (int j = 0; j < canvas->uiComponents.size; j++) {
            void (*event_draw)(void *, UICanvas *) = *(void (**)(void *, UICanvas *))((char *)canvas->uiComponents.items[j] + sizeof(void (*)(void *, UICanvas *)) * 2);
            if (event_draw != NULL) {
                event_draw(canvas->uiComponents.items[j], canvas);
            }
        }
    }

#ifndef NDEBUG

    if (debugShowStats) {
        SDL_Color color = {255, 255, 255, 255};
        char statsBuff[256];

        snprintf(statsBuff, 256, "FPS: %.2f", 1.0 / getDeltaTime());

        statsTextSurface = TTF_RenderText_Solid(debugFont, statsBuff, color);
        statsTextTexture = SDL_CreateTextureFromSurface(r->gameRenderer, statsTextSurface);

        SDL_Rect statsTextRect = {.x = 5, .y = 5, .w = statsTextSurface->w, statsTextSurface->h};
        SDL_RenderCopy(r->gameRenderer, statsTextTexture, NULL, &statsTextRect);

        SDL_FreeSurface(statsTextSurface);
        SDL_DestroyTexture(statsTextTexture);
    }

#endif

    SDL_RenderPresent(r->gameRenderer);
}

Vector2 renderer_getViewportLocation() {
    if (getRenderer()->focusedCamera == NULL)
        return VECTOR2_ZERO;

    return getRenderer()->focusedCamera->_viewportWorldLocation;
}

void renderer_rectAdjustByCamera(SDL_Rect *rect) {
    rect->x -= renderer_getViewportLocation().x;
    rect->y -= renderer_getViewportLocation().y;
}

void renderer_UI_drawFillRectangle(Color *color, Vector2 *location, Vector2 *size) {
    SDL_SetRenderDrawColor(getRenderer()->gameRenderer, color->r, color->g, color->b, color->a);

    SDL_Rect rect = {
        .x = location->x,
        .y = location->y,
        .w = size->x,
        .h = size->y};

    SDL_RenderFillRect(getRenderer()->gameRenderer, &rect);
}

void renderer_UI_drawRectangle(Color *color, Vector2 *location, Vector2 *size) {
    SDL_SetRenderDrawColor(getRenderer()->gameRenderer, color->r, color->g, color->b, color->a);

    SDL_Rect rect = {
        .x = location->x,
        .y = location->y,
        .w = size->x,
        .h = size->y};

    SDL_RenderDrawRect(getRenderer()->gameRenderer, &rect);
}

void renderer_drawFillRectangle(Color *color, Vector2 *location, Vector2 *size) {
    SDL_SetRenderDrawColor(getRenderer()->gameRenderer, color->r, color->g, color->b, color->a);

    SDL_Rect rect = {
        .x = location->x,
        .y = location->y,
        .w = size->x,
        .h = size->y};

    renderer_rectAdjustByCamera(&rect);

    SDL_RenderFillRect(getRenderer()->gameRenderer, &rect);
}

void renderer_drawRectangle(Color *color, Vector2 *location, Vector2 *size) {
    SDL_SetRenderDrawColor(getRenderer()->gameRenderer, color->r, color->g, color->b, color->a);

    SDL_Rect rect = {
        .x = location->x,
        .y = location->y,
        .w = size->x,
        .h = size->y};

    renderer_rectAdjustByCamera(&rect);

    SDL_RenderDrawRect(getRenderer()->gameRenderer, &rect);
}