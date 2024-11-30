#include "engineCore.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "appManager.h"
#include "buttonUIComponent.h"
#include "fileHelper.h"
#include "gameLoop.h"
#include "level.h"
#include "logger.h"
#include "physicsGameObjectComp.h"
#include "renderer.h"
#include "time.h"
#include "uiCanvas.h"

EngineCore _engineCore;
Level _currentLevel;

GameObject* _focusedGameObject = NULL;

Uint64 _lastTime;

double _deltaTime;

void engineCore_startGameEngine(EngineOptions* options, EngineEvents* events, int argc, const char* argv[]) {
    char appParentFolderPath[255];

    getParentDirectoryPath(argv[0], appParentFolderPath);
    logger_init(strcat(appParentFolderPath, "/log.txt"));

#ifdef DEBUG
    LOG("Running engine in DEBUG configuration.");
#endif

#ifdef NDEBUG
    LOG("Running engine in RELEASE configuration.");
#endif

    LOG("Starting application...");

    LOG("Initializing engine core...");
    _engineCore_initialize(options, events);
    LOG("Engine core initialized.");

    LOG("Initializing SDL...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG_E("Could not initialize SDL: %s\n", SDL_GetError());
        logger_stop();

        cleanupApp();
        quitApp(1);
    }
    LOG("SDL initialized.");

    // Initialize renderer
    if (renderer_init() == -1) {
        cleanupApp();
        quitApp(1);
    }

    // Call initialized function
    if (getCore()->events.event_engineInitialized != NULL)
        getCore()->events.event_engineInitialized();

    // Start the game loop
    gameLoop_start();

    // Start cleanup after gameLoop ends
    cleanupApp();

    quitApp(0);
}

EngineCore* getCore() {
    return &_engineCore;
}

Level* getLevel() {
    return &_currentLevel;
}

double getDeltaTime() {
    return _deltaTime;
}

GameObject* getFocusedGameObject() {
    return _focusedGameObject;
}

void _engineCore_initialize(EngineOptions* _options, EngineEvents* _events) {
    getCore()->options = *_options;
    getCore()->events = *_events;

    engineCore_loadLevel(&getCore()->options.initialLevel);

    _lastTime = SDL_GetPerformanceCounter();

    srand(time(NULL));
}

void _engineCore_clean() {
    _engineCore_cleanGameObjects();
}

void _engineCore_cleanGameObjects() {
    // Clean allGameObjects array
    for (size_t i = 0; i < getLevel()->allGameObjects.size; i++) {
        free(getLevel()->allGameObjects.items[i]);
        getLevel()->allGameObjects.items[i] = NULL;
    }

    ARRAY_CLEAN(getLevel()->allGameObjects);
}

void _engineCore_tick() {
    // Calculate delta time
    Uint64 currentTime = SDL_GetPerformanceCounter();
    _deltaTime = (double)(currentTime - _lastTime) / (double)SDL_GetPerformanceFrequency();
    _lastTime = currentTime;

    // Call tick event on every game object
    for (size_t i = 0; i < getLevel()->allGameObjects.size; i++) {
        GameObject* go = getLevel()->allGameObjects.items[i];

        // Handle parent's properties
        if (go->parentGameObject != NULL) {
            go->location = go->parentGameObject->location;
        }

        // Call tick event on components
        if (go->components.size != 0) {
            for (size_t i = 0; i < go->components.size; i++) {
                void* comp = go->components.items[i];
                // event_registered (void*, GameObject*)
                // event_tick (void*, GameObject*)
                // event_draw (void*, GameObject*)
                // event_destroyed (void*, GameObject*)
                // id (size_t)
                // relativeLocation (Vector2)
                // worldLocation (Vector2)
                // size (Vector2)

                Vector2* relativeLoc = (Vector2*)((char*)comp + (sizeof(void (*)(void*, GameObject*)) * GAMEOBJECTCOMP_EVENT_COUNT) + sizeof(size_t));
                Vector2* worldLoc = (Vector2*)(relativeLoc + sizeof(Vector2));

                // Set world location
                worldLoc->x = go->location.x + relativeLoc->x;
                worldLoc->y = go->location.y + relativeLoc->y;

                void (*event_tick)(void*, GameObject*) = *(void (**)(void*, GameObject*))((char*)comp + sizeof(void (*)(void*, GameObject*)));
                if (event_tick != NULL)
                    event_tick(comp, go);
            }
        }

        // Call tick event
        if (go->event_tick != NULL)
            go->event_tick(go);
    }

    // Call tick event on every UI canvas
    for (int i = 0; i < getCore()->allUICanvases.size; i++) {
        UICanvas* canvas = getCore()->allUICanvases.items[i];

        // Call tick event on components
        for (int j = 0; j < canvas->uiComponents.size; j++) {
            void* comp = canvas->uiComponents.items[j];
            int m_x, m_y;
            Uint32 mouseState = SDL_GetMouseState(&m_x, &m_y);
            Vector2 mousePos = VECTOR2((float)m_x, (float)m_y);

            /*  void*, UICanvas* event_registered
                event_tick
                event_draw
                event_destroyed
                event_clicked
                event_pressed
                event_released
                event_hovered
                event_unhovered
                size_t id
                Vector2 position
                Vector2 size
                Visibility visibility
                int isPressed
                int isHovered
                int disabled
            */
            void (*event_tick)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)));
            void (*event_draw)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 2);
            void (*event_destroyed)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 3);
            void (*event_clicked)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 4);
            void (*event_pressed)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 5);
            void (*event_released)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 6);
            void (*event_hovered)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 7);
            void (*event_unhovered)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 8);
            size_t* id = (size_t*)((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 9);
            Vector2* position = (Vector2*)((char*)id + sizeof(size_t));
            Vector2* size = (Vector2*)((char*)position + sizeof(Vector2));
            Visibility* visibility = (Visibility*)((char*)size + sizeof(Vector2));
            int* isPressed = (int*)((char*)visibility + sizeof(Visibility));
            int* isHovered = (int*)((char*)isPressed + sizeof(int));
            int* disabled = (int*)((char*)isHovered + sizeof(int));

            SDL_Rect compRect = vector2x2toSDL_Rect(position, size),
                     mouseRect = vector2x2toSDL_Rect(&mousePos, &VECTOR2(1, 1));

            // LOG("Mouse rect: %d, %d Comp rect: %d, %d, %d, %d", mouseRect.x, mouseRect.y, compRect.x, compRect.y, compRect.w, compRect.h);

            // Is mouse over the UI Component
            if ((*visibility) != VISIBILITY_COLLAPSED && SDL_HasIntersection(&compRect, &mouseRect)) {
                // Hovered
                (*isHovered) = TRUE;
                if (event_hovered != NULL) {
                    event_hovered(comp, canvas);
                }

                // Pressed LMB
                if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    (*isPressed) = TRUE;
                    if (event_pressed != NULL)
                        event_pressed(comp, canvas);
                } else if ((*isPressed)) {  // Is no longer pressed
                    (*isPressed) = FALSE;
                    if (event_released != NULL)
                        event_released(comp, canvas);

                    // Click the button
                    if (event_clicked != NULL)
                        event_clicked(comp, canvas);
                }
            } else {  // Is not hovered
                // Was hovered
                if ((*isHovered)) {
                    (*isHovered) = FALSE;
                    if (event_unhovered != NULL)
                        event_unhovered(comp, canvas);
                }

                // Was pressed
                if ((*isPressed)) {
                    (*isPressed) = FALSE;
                    if (event_released != NULL)
                        event_released(comp, canvas);
                }
            }

            if (event_tick != NULL)
                event_tick(comp, canvas);
        }

        // Call tick event
        if (canvas->event_tick != NULL)
            canvas->event_tick(canvas);
    }
}

void _engineCore_anyInput(SDL_Event* event) {
    SDL_Keycode code = event->key.keysym.sym;

#ifndef NDEBUG
    // Debug keys
    if (event->type == SDL_KEYDOWN) {
        if (code == SDLK_F1) {
            debugShowStats = !debugShowStats;
        } else if (code == SDLK_F2) {
            debugShowCollisions = !debugShowCollisions;
        }
    }

#endif

    if (getCore()->events.event_anyInput != NULL) getCore()->events.event_anyInput(event);
}

int engineCore_loadLevel(Level* level) {
    LOG("Requested to load level \"%s\".", level->name);

    if (level->name == NULL) {
        LOG_E("Failed to load level! Level name is NULL.");
        cleanupApp();
        exit(1);
    }

    // Check ID
    if (level->id == 0) {
        LOG_W("Level does not have an ID. This could cause issues in the future.");
    }

    // Check loaded
    if (level->event_loaded == NULL) {
        LOG_W("Level does not have a pointer to the \"loaded\" function. This could cause issues in the future.");
    }

    LOG("Cleaning game objects in the current level.");
    _engineCore_cleanGameObjects();

    LOG("Transitioning from \"%s\" to \"%s\"...", getLevel()->name, level->name);
    _currentLevel = *level;

    LOG("Initializing new level...");
    ARRAY_INIT(getLevel()->allGameObjects);
    LOG("Level initialized.");

    LOG("Level \"%s\" loaded successfully.", getLevel()->name);
    if (getLevel()->event_loaded != NULL)
        getLevel()->event_loaded();

    return 1;
}

GameObject* _engineCore_registerGameObject(GameObject* go) {
    GameObject* _go = (GameObject*)malloc(sizeof(GameObject));

    (*_go) = (*go);

    ARRAY_ADD(getLevel()->allGameObjects, GameObject*, _go);

    return _go;
}

int _engineCore_unregisterGameObject(size_t id) {
    Level* l = getLevel();

    for (size_t i = 0; i < l->allGameObjects.size; i++) {
        if (l->allGameObjects.items[i]->id == id) {
            if (l->allGameObjects.items[i]->event_destroyed != NULL)
                l->allGameObjects.items[i]->event_destroyed(l->allGameObjects.items[i]);

            ARRAY_REMOVE_CLEAN(l->allGameObjects, GameObject*, i);

            return 1;
        }
    }

    return 0;
}

UICanvas* _engineCore_registerUICanvas(UICanvas* canvas) {
    UICanvas* _canvas = (UICanvas*)malloc(sizeof(UICanvas));

    (*_canvas) = (*canvas);

    ARRAY_ADD(getCore()->allUICanvases, UICanvas*, _canvas);

    return _canvas;
}

int _engineCore_unregisterUICanvas(size_t id) {
    EngineCore* ec = getCore();

    for (size_t i = 0; i < ec->allUICanvases.size; i++) {
        if (ec->allUICanvases.items[i]->id == id) {
            if (ec->allUICanvases.items[i]->event_destroyed != NULL)
                ec->allUICanvases.items[i]->event_destroyed(ec->allUICanvases.items[i]);

            ARRAY_REMOVE_CLEAN(ec->allUICanvases, UICanvas*, i);

            return 1;
        }
    }

    return 0;
}

/**
 * Sends input to this game object.
 */
void engineCore_focusGameObject(GameObject* go) {
    _focusedGameObject = go;
}