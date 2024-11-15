#include <stdio.h>
#include "BeEngine.h"
#include "array.h"
#include "testLevel.h"

void event_gameEngineInitialized();
void event_tick();
void event_draw();
void event_anyInput(SDL_Event *event);
void event_beginOverlap(GameObject *self, GameObject *collidedWith);
void event_endOverlap(GameObject *self, GameObject *collidedWith);

int main(int argc, const char* argv[]) {
    EngineOptions options = {
        .projectName = "Breaker (BeEngine)",
        .window_x = 200,
        .window_y = 200,
        .window_width = 800,
        .window_height = 600,
        .initialLevel = testLevel
    };

    EngineEvents events = {
        .event_engineInitialized = &event_gameEngineInitialized,
        .event_anyInput = &event_anyInput
    };
    
    engineCore_startGameEngine(&options, &events, argc, argv);
}

GameObject *player;

void event_gameEngineInitialized() {
    player = REG_GAMEOBJECT(&GAMEOBJECT(10, VECTOR2(10, 10), ((Vector2) {.x = 10, .y = 10}), NULL, &event_draw));
    player->objectType = MOVABLE;
    player->event_beginOverlap = &event_beginOverlap;
    player->event_endOverlap = &event_endOverlap;
}

// Přidávat pozici na ticku (Pak udělat physics systém kde stačí dát velocity).
// Podle keydown se nastaví velocity a výpočty se provedou v physicsEngine.c
void event_anyInput(SDL_Event *event) {
    SDL_Keycode code = event->key.keysym.sym;

    if (event->type == SDL_KEYDOWN) {
        if (code == SDLK_a) player->velocity.x = -100;
        else if (code == SDLK_d) player->velocity.x = 100;
        else if (code == SDLK_w) player->velocity.y = 100;
        else if (code == SDLK_s) player->velocity.y = -100;
    } else if (event->type == SDL_KEYUP) {
        if (code == SDLK_a && player->velocity.x == -100) player->velocity.x = 0;
        else if (code == SDLK_d && player->velocity.x == 100) player->velocity.x = 0;
        else if (code == SDLK_w && player->velocity.y == 100) player->velocity.y = 0;
        else if (code == SDLK_s && player->velocity.y == -100) player->velocity.y = 0;
    }
}

void event_draw() {
    renderer_fillRectangle(&COLOR(255, 0, 0), &player->position, &player->size);
}

void event_beginOverlap(GameObject *self, GameObject *collidedWith) {
    LOG("Begin overlap!");
}

void event_endOverlap(GameObject *self, GameObject *collidedWith) {
    LOG("End overlap!");
}