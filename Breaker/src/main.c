#include <stdio.h>

#include "BeEngine.h"
#include "array.h"
#include "gameObject.h"
#include "physicsGameObjectComp.h"
#include "testLevel.h"
#include "textureGameObjectComp.h"

void event_gameEngineInitialized();
void event_tick();
void event_draw();
void event_anyInput(SDL_Event *event);
void event_beginOverlap(GameObject *self, GameObject *collidedWith);
void event_endOverlap(GameObject *self, GameObject *collidedWith);

int main(int argc, const char *argv[]) {
    EngineOptions options = {
        .projectName = "Breaker (BeEngine)",
        .window_x = SDL_WINDOWPOS_CENTERED,
        .window_y = SDL_WINDOWPOS_CENTERED,
        .window_width = 800,
        .window_height = 600,
        .initialLevel = testLevel};

    EngineEvents events = {
        .event_engineInitialized = &event_gameEngineInitialized,
        .event_anyInput = &event_anyInput};

    engineCore_startGameEngine(&options, &events, argc, argv);
}

GameObject *player;
PhysicsGameObjectComp test;
TextureGameObjectComp texture;

void event_gameEngineInitialized() {
    player = REG_GAMEOBJECT(&GAMEOBJECT(VECTOR2(10, 10), VECTOR2(10, 10), NULL, &event_draw));
    player->objectType = MOVABLE;
    player->event_beginOverlap = &event_beginOverlap;
    player->event_endOverlap = &event_endOverlap;

    // Automaticky bindovat eventy
    test = (PhysicsGameObjectComp){.id = 1, .event_tick = &_PhysicsGameObjectComp_tick};
    texture = (TextureGameObjectComp){.id = 2, .event_registered = &_TextureGameObjectComp_registered, .event_draw = &_TextureGameObjectComp_draw, .imagePath = "./assets/textures/saddam.png"};
    // GAMEOBJECT_ATTACH_COMPONENT(PhysicsGameObjectComp, &test);
    gameObject_attachComponent(player, &test);
}

// Přidávat pozici na ticku (Pak udělat physics systém kde stačí dát velocity).
// Podle keydown se nastaví velocity a výpočty se provedou v physicsEngine.c
void event_anyInput(SDL_Event *event) {
    SDL_Keycode code = event->key.keysym.sym;

    float vel = 50;

    if (event->type == SDL_KEYDOWN) {
        if (code == SDLK_a)
            player->velocity.x = -vel;
        else if (code == SDLK_d)
            player->velocity.x = vel;
        else if (code == SDLK_w)
            player->velocity.y = vel;
        else if (code == SDLK_s)
            player->velocity.y = -vel;
    } else if (event->type == SDL_KEYUP) {
        if (code == SDLK_a && player->velocity.x == -vel)
            player->velocity.x = 0;
        else if (code == SDLK_d && player->velocity.x == vel)
            player->velocity.x = 0;
        else if (code == SDLK_w && player->velocity.y == vel)
            player->velocity.y = 0;
        else if (code == SDLK_s && player->velocity.y == -vel)
            player->velocity.y = 0;
    }
}

void event_draw() {
    renderer_drawFillRectangle(&COLOR(255, 0, 0), &player->position, &player->size);
}

void event_beginOverlap(GameObject *self, GameObject *collidedWith) {
    LOG("Begin overlap!");
}

void event_endOverlap(GameObject *self, GameObject *collidedWith) {
    LOG("End overlap!");
}