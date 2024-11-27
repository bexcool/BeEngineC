#include "renderer.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "appManager.h"
#include "color.h"
#include "engineCore.h"
#include "gameObject.h"
#include "logger.h"
#include "objSquare.h"
#include "vector2.h"

SDL_Renderer *gameRenderer;
SDL_Window *gameWindow;

SDL_Texture *saddamTexture;
SDL_Surface *surfaceMessage, *statsTextSurface;
SDL_Texture *textureMessage, *statsTextTexture;
TTF_Font *font;

#ifndef NDEBUG

int debugShowStats = 0, debugShowCollisions = 0;

#endif

int renderer_init() {
    LOG("Initializing renderer...");

    EngineOptions opt = getCore()->options;

    LOG("Renderer: Creating SDL window...");
    gameWindow = SDL_CreateWindow(
        opt.projectName,
        opt.window_x,
        opt.window_y,
        opt.window_width,
        opt.window_height,
        SDL_WINDOW_SHOWN);

    if (gameWindow == NULL) {
        LOG_E("Renderer: Could not create window: %s\n", SDL_GetError());
        return -1;
    }
    LOG("Renderer: SDL window created.");

    LOG("Renderer: Creating SDL renderer...");
    gameRenderer = SDL_CreateRenderer(
        gameWindow,
        -1,
        SDL_RENDERER_ACCELERATED);  //| SDL_RENDERER_PRESENTVSYNC);

    if (gameRenderer == NULL) {
        LOG_E("Renderer: Could not create renderer: %s\n", SDL_GetError());
        return -1;
    }
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

    saddamTexture = IMG_LoadTexture(gameRenderer, "./assets/textures/saddam.png");
    font = TTF_OpenFont("./assets/fonts/AvrileSansUI-Regular.ttf", 24);

    SDL_Color color = {255, 255, 255, 255};

    surfaceMessage = TTF_RenderText_Solid(font, "KVARK RULES!", color);
    textureMessage = SDL_CreateTextureFromSurface(gameRenderer, surfaceMessage);

    LOG("Renderer initialized.");

    return 0;
}

void renderer_render() {
    static size_t frame = 0;
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gameRenderer);

    Level *l = getLevel();

    for (size_t i = 0; i < l->allGameObjects.size; i++) {
        GameObject *go = l->allGameObjects.items[i];

        go->event_draw(l->allGameObjects.items[i]);

        for (size_t j = 0; j < go->components.size; j++) {
            void *comp = go->components.items[j];

            void (*event_draw)(void *, GameObject *) = *(void (**)(void *, GameObject *))(comp + (sizeof(void (*)(void *, GameObject *)) * 2));
            if (event_draw != NULL)
                event_draw(go->components.items[i], go);
        }

#ifndef NDEBUG

        if (debugShowStats) {
            SDL_Color color = {255, 255, 255, 255};
            char statsBuff[256];

            snprintf(statsBuff, 256, "FPS: %.2f", 1.0 / getDeltaTime());

            statsTextSurface = TTF_RenderText_Solid(font, statsBuff, color);
            statsTextTexture = SDL_CreateTextureFromSurface(gameRenderer, statsTextSurface);

            SDL_Rect statsTextRect = {.x = 5, .y = 5, .w = surfaceMessage->w, surfaceMessage->h};
            SDL_RenderCopy(gameRenderer, statsTextTexture, NULL, &statsTextRect);

            SDL_FreeSurface(statsTextSurface);
            SDL_DestroyTexture(statsTextTexture);
        }

        if (debugShowCollisions) {
            renderer_drawRectangle(&COLOR(255, 0, 0), &VECTOR2(go->position.x, go->position.y), &VECTOR2(go->size.x, go->size.y));
            SDL_RenderDrawLine(gameRenderer, go->position.x, go->position.y, go->position.x + go->size.x - 1, go->position.y + go->size.y - 1);
            SDL_RenderDrawLine(gameRenderer, go->position.x, go->position.y + go->size.y - 1, go->position.x + go->size.x - 1, go->position.y);
        }

#endif
    }

    SDL_Rect textRect = {.x = 500, .y = 20, .w = surfaceMessage->w, surfaceMessage->h};
    // TTF_SizeText(font, "put your text here", &textRect.w, &textRect.h);
    SDL_RenderCopy(gameRenderer, textureMessage, NULL, &textRect);

    SDL_Rect dstRect = {500, 100, 356, 200};  // Destination rectangle (x, y, w, h)
    SDL_RenderCopy(gameRenderer, saddamTexture, NULL, &dstRect);

    SDL_RenderPresent(gameRenderer);
}

void renderer_drawFillRectangle(const Color *color, const Vector2 *position, const Vector2 *size) {
    SDL_SetRenderDrawColor(gameRenderer, color->r, color->g, color->b, color->a);

    SDL_Rect rect = {
        .x = position->x,
        .y = position->y,
        .w = size->x,
        .h = size->y};

    SDL_RenderFillRect(gameRenderer, &rect);
}

void renderer_drawRectangle(const Color *color, const Vector2 *position, const Vector2 *size) {
    SDL_SetRenderDrawColor(gameRenderer, color->r, color->g, color->b, color->a);

    SDL_Rect rect = {
        .x = position->x,
        .y = position->y,
        .w = size->x,
        .h = size->y};

    SDL_RenderDrawRect(gameRenderer, &rect);
}