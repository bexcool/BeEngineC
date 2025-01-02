#include "engineCore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "SDL.h"
#include "appManager.h"
#include "buttonUIComponent.h"
#include "constraint.h"
#include "fileHelper.h"
#include "gameLoop.h"
#include "level.h"
#include "logger.h"
#include "physicsGameObjectComp.h"
#include "renderer.h"
#include "sound.h"
#include "time.h"
#include "uiCanvas.h"

EngineCore ___engineCore;
Uint64 _lastTime;

double _deltaTime;

void engineCore_startGameEngine(EngineOptions* options, EngineEvents* events, int argc, const char* argv[]) {
    char loggerFilePath[256];

    getParentDirectoryPath(argv[0], ___engineCore._executableFolderPath);
    strcpy(loggerFilePath, ___engineCore._executableFolderPath);
    strcat(loggerFilePath, "/log.txt");

    logger_init(loggerFilePath);

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
        quitApp(1);
    }
    LOG("SDL initialized.");

    // Initialize renderer
    if (renderer_init() < 0) {
        quitApp(1);
    }

    // Initialize sound
    if (sound_init() < 0) {
        quitApp(1);
    }

    // Call initialized function
    if (getCore()->events.event_engineInitialized != NULL)
        getCore()->events.event_engineInitialized();

    // Load initial level
    engineCore_loadLevel(&getCore()->options.initialLevel);

    // Start the game loop
    gameLoop_start();

    // Quit the application (Also cleans up)
    quitApp(0);
}

// Getters
EngineCore* getCore() {
    return &___engineCore;
}

Level* getLevel() {
    return &getCore()->_currentLevel;
}

Renderer* getRenderer() {
    return &getCore()->_renderer;
}

double getDeltaTime() {
    return _deltaTime;
}

char* getExecutableFolderPath() {
    return ___engineCore._executableFolderPath;
}

void _engineCore_initialize(EngineOptions* _options, EngineEvents* _events) {
    getCore()->options = *_options;
    getCore()->events = *_events;

    _lastTime = SDL_GetPerformanceCounter();

    srand(time(NULL));
}

void _engineCore_clean() {
    _engineCore_cleanGameObjects();
    _engineCore_cleanUICanvases();
}

void _engineCore_cleanGameObjects() {
    if (getLevel()->allGameObjects.size == 0) return;
    if (TRUE) {
        // Temp (Je to ale memory leak :/)
        for (size_t i = 0; i < getLevel()->allGameObjects.size; i++) {
            GameObject* go = getLevel()->allGameObjects.items[0];

            if (go == NULL) {
                LOG_E("Engine core: Clean game objects: Game object is NULL at index %d", i);
                continue;
            }

            go->location = VECTOR2(-1000, 0);
        }

        return;
    }

    // Clean allGameObjects list
    int iLoops = getLevel()->allGameObjects.size;
    for (size_t i = 0; i < iLoops; i++) {
        GameObject* go = getLevel()->allGameObjects.items[0];

        int jLoops = go->components.size;
        for (size_t j = 0; j < jLoops; j++) {
            void* comp = go->components.items[0];
            if (comp == NULL) {
                LOG_E("Engine core: Clean game objects: Component is NULL at index %d", j);
                continue;
            }

            void (*event_destroyed)(void*, GameObject*) = *(void (**)(void*, GameObject*))((char*)comp + sizeof(void (*)(void*, GameObject*)) * 3);
            if (event_destroyed != NULL)
                event_destroyed(comp, go);

            LIST_REMOVE_CLEAN(go->components, void*, 0);
        }
        LIST_CLEAN(go->components);

        if (go->event_destroyed)
            go->event_destroyed(go);

        LIST_REMOVE_CLEAN(getLevel()->allGameObjects, GameObject*, 0);
    }

    LIST_CLEAN(getLevel()->allGameObjects);
}

void _engineCore_cleanUICanvases() {
    if (getLevel()->allUICanvases.size == 0) return;

    // Temp (Je to ale memory leak :/)
    // Kvůli tomuto: Ale nedává to smysl, crashne to až po načtení levelu co se načte fully.
    /*
    AddressSanitizer: heap-use-after-free on address 0x606000092790 at pc 0x0001027e9718 bp 0x00016d68a7d0 sp 0x00016d68a7c8
    READ of size 8 at 0x606000092790 thread T0
    #0 0x1027e9714 in _engineCore_tickUI engineCore.c:272
    #1 0x1027e8908 in _engineCore_tick engineCore.c:204
    #2 0x1027eea6c in gameLoop_start gameLoop.c:36
    #3 0x1027e612c in engineCore_startGameEngine engineCore.c:72
    #4 0x10277ec28 in main main.c:30 #5 0x18576c270 (<unknown module>)
    */
    for (size_t i = 0; i < getLevel()->allUICanvases.size; i++) {
        for (size_t j = 0; j < getLevel()->allUICanvases.items[i]->uiComponents.size; j++) {
            void* comp = getLevel()->allUICanvases.items[i]->uiComponents.items[j];
            if (comp == NULL) {
                LOG_E("Engine core: Clean UI canvases: Component is NULL at index %d", j);
                continue;
            }

            void (*event_destroyed)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 3);
            if (event_destroyed != NULL)
                event_destroyed(comp, getLevel()->allUICanvases.items[i]);

            // get visibility from comp
            Visibility* visibility = (Visibility*)((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 9 + sizeof(size_t) + sizeof(char) * 64 + sizeof(Vector2) * 2 + sizeof(Thickness));
            (*visibility) = VISIBILITY_HIDDEN;
        }
    }

    return;

    // Clean allUICanvases list
    for (size_t i = 0; i < getLevel()->allUICanvases.size; i++) {
        UICanvas* canvas = getLevel()->allUICanvases.items[i];
        if (canvas == NULL) {
            LOG_E("Engine core: Clean UI canvases: Canvas is NULL at index %d", i);
            continue;
        }

        for (size_t j = 0; j < canvas->uiComponents.size; j++) {
            void* comp = canvas->uiComponents.items[j];
            if (comp == NULL) {
                LOG_E("Engine core: Clean UI canvases: Component is NULL at index %d", j);
                continue;
            }

            void (*event_destroyed)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 3);
            if (event_destroyed != NULL)
                event_destroyed(comp, canvas);

            free(comp);
            canvas->uiComponents.items[j] = NULL;
        }
        LIST_CLEAN(canvas->uiComponents);

        if (canvas->event_destroyed)
            canvas->event_destroyed(canvas);

        free(canvas);
        getLevel()->allUICanvases.items[i] = NULL;
    }

    LIST_CLEAN(getLevel()->allUICanvases);
}

void _engineCore_tick() {
    // Calculate delta time
    Uint64 currentTime = SDL_GetPerformanceCounter();
    _deltaTime = (double)(currentTime - _lastTime) / (double)SDL_GetPerformanceFrequency();
    _lastTime = currentTime;

    // Do not tick if loading level
    if (getCore()->_loadingLevel) return;

    _engineCore_tickGameObjects();
    _engineCore_tickUI();
}

void _engineCore_tickGameObjects() {
    // Call tick event on every game object
    for (size_t i = 0; i < getLevel()->allGameObjects.size; i++) {
        GameObject* go = getLevel()->allGameObjects.items[i];

        if (go == NULL) {
            LOG_W("Engine core: Tick game objects: Game object is NULL at index %d", i);
            continue;
        }

        // Handle parent's properties
        if (go->parentGameObject != NULL) {
            go->location = vector2_add(&go->parentGameObject->location, &go->relativeLocation);
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

                if (comp == NULL) {
                    LOG_W("Engine core: Tick game objects: Component is NULL at index %d in game object with ID: ", i, go->id);
                    continue;
                }

                Vector2* relativeLoc = (Vector2*)((char*)comp + (sizeof(void (*)(void*, GameObject*)) * GAMEOBJECTCOMP_EVENT_COUNT) + sizeof(size_t));
                Vector2* worldLoc = (Vector2*)((char*)relativeLoc + sizeof(Vector2));

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
}

void _engineCore_tickUI() {
    SDL_Rect viewport;
    SDL_RenderGetViewport(getRenderer()->gameRenderer, &viewport);

    // Call tick event on every UI canvas
    for (size_t i = 0; i < getLevel()->allUICanvases.size; i++) {
        UICanvas* canvas = getLevel()->allUICanvases.items[i];

        if (canvas == NULL) {
            LOG_E("Engine core: Tick UI: Canvas is NULL at index %d", i);
            continue;
        }

        // Call tick event on components
        for (size_t j = 0; j < canvas->uiComponents.size; j++) {
            void* comp = canvas->uiComponents.items[j];
            if (comp == NULL) {
                LOG_E("Engine core: Tick UI: Component is NULL at index %d", j);
                continue;
            }

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
                event_input
                size_t id
                char displayName[64]
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
            void (*event_input)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 9);
            size_t* id = (size_t*)((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 10);
            char* displayName = (char*)((char*)id + sizeof(size_t));
            Vector2* position = (Vector2*)((char*)displayName + sizeof(char) * 64);
            Vector2* _actualPosition = (Vector2*)((char*)position + sizeof(Vector2));
            Thickness* margin = (Thickness*)((char*)_actualPosition + sizeof(Vector2));
            Vector2* size = (Vector2*)((char*)margin + sizeof(Thickness));
            Visibility* visibility = (Visibility*)((char*)size + sizeof(Vector2));
            int* isPressed = (int*)((char*)visibility + sizeof(Visibility));
            int* isHovered = (int*)((char*)isPressed + sizeof(int));
            int* disabled = (int*)((char*)isHovered + sizeof(int));
            ConstraintType* horizontalConstraint = (ConstraintType*)((char*)disabled + sizeof(int));
            ConstraintType* verticalConstraint = (ConstraintType*)((char*)horizontalConstraint + sizeof(ConstraintType));

            (*_actualPosition) = constraint_apply(&TRANSFORM(VECTOR2_ZERO, VECTOR2(viewport.w, viewport.h)),
                                                  &TRANSFORM(*position, *size),
                                                  margin,
                                                  *horizontalConstraint,
                                                  *verticalConstraint);

            SDL_Rect compRect = vector2x2toSDL_Rect(_actualPosition, size),
                     mouseRect = vector2x2toSDL_Rect(&mousePos, &VECTOR2(1, 1));

            if (engineCore_getInputFocus() != INPUT_GAME) {
                // Is mouse over the UI Component
                if ((*visibility) != VISIBILITY_COLLAPSED && SDL_HasIntersection(&compRect, &mouseRect)) {
                    // Hovered
                    (*isHovered) = TRUE;
                    if (event_hovered != NULL) {
                        event_hovered(comp, canvas);
                    }

                    // Pressed LMB
                    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                        if (event_pressed != NULL && !(*isPressed))
                            event_pressed(comp, canvas);

                        (*isPressed) = TRUE;
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
            }

            if (event_tick != NULL)
                event_tick(comp, canvas);
        }

        // Call tick event
        if (canvas->event_tick != NULL) {
            canvas->event_tick(canvas);
        }
    }
}

void _engineCore_anyInput(SDL_Event* event) {
    getCore()->lastInputEvent = event;
    Renderer* r = getRenderer();

    // TODO: Call this only when event happened

    SDL_Keycode code = event->key.keysym.sym;

#ifndef NDEBUG
    // Debug keys
    if (event->type == SDL_KEYDOWN) {
        if (code == SDLK_F1) {
            r->debugShowStats = !r->debugShowStats;
        } else if (code == SDLK_F2) {
            r->debugShowCollisions = !r->debugShowCollisions;
        }
    }

#endif

    if (engineCore_getInputFocus() != INPUT_UI) {
        if (getCore()->events.event_anyInput != NULL) getCore()->events.event_anyInput(event);
    }

    if (engineCore_getInputFocus() != INPUT_GAME && engineCore_getFocusedUIComponent() != NULL) {
        void (*event_input)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)engineCore_getFocusedUIComponent() + sizeof(void (*)(void*, UICanvas*)) * 9);

        if (event_input != NULL) {
            event_input(engineCore_getFocusedUIComponent(), engineCore_getFocusedUICanvas());
        }
    }
}

GameObject* _engineCore_registerGameObject(GameObject* go) {
    GameObject* _go = (GameObject*)malloc(sizeof(GameObject));

    (*_go) = (*go);

    LIST_INIT(_go->components);

    LIST_ADD(getLevel()->allGameObjects, GameObject*, _go);

    return _go;
}

void _engineCore_unregisterGameObject(GameObject* go) {
    Level* l = getLevel();

    // Remove 'go' from others' overlapped lists
    for (size_t i = 0; i < l->allGameObjects.size; i++) {
        GameObject* other = l->allGameObjects.items[i];
        if (other && LIST_CONTAINS(other->overlappedGameObjects, GameObject*, ->id, go->id)) {
            size_t index = LIST_FIND_INDEX(other->overlappedGameObjects, GameObject*, ->id, go->id);
            if (index != -1) {
                LIST_REMOVE(other->overlappedGameObjects, GameObject*, index);
            }
        }
    }

    if (go->event_destroyed != NULL)
        go->event_destroyed(go);

    for (size_t j = 0; j < go->components.size; j++) {
        LOG("Engine core: Unregister game object: Cleaning component at index %zu with pointer %p", j, go->components.items[j]);

        void* comp = go->components.items[j];
        if (comp == NULL) {
            LOG_E("Engine core: Unregister game object: Component is NULL at index %zu", j);
            continue;
        }

        void (*event_destroyed)(void*, GameObject*) = *(void (**)(void*, GameObject*))((char*)comp + sizeof(void (*)(void*, GameObject*)) * 3);
        if (event_destroyed != NULL)
            event_destroyed(comp, go);

        free(comp);
        go->components.items[j] = NULL;
    }

    LIST_CLEAN(go->components);

    int indexToRemove = LIST_FIND_INDEX(l->allGameObjects, GameObject*, , go);
    if (indexToRemove >= 0) {
        LOG("Engine core: Game object with ID %d (P: %p) unregistered.", go->id, go);
        LIST_REMOVE_CLEAN(l->allGameObjects, GameObject*, indexToRemove);
    } else {
        LOG_E("Engine core: Unregister game object: Game object not found in allGameObjects");
    }
}

UICanvas* _engineCore_registerUICanvas() {
    UICanvas* canvas = (UICanvas*)malloc(sizeof(UICanvas));

    canvas->id = rand() % SIZE_T_MAX + 1;
    canvas->visibility = VISIBILITY_VISIBLE;
    canvas->event_register = NULL;
    canvas->event_tick = NULL;
    canvas->event_destroyed = NULL;

    LIST_INIT(canvas->uiComponents);

    LIST_ADD(getLevel()->allUICanvases, UICanvas*, canvas);

    return canvas;
}

void _engineCore_unregisterUICanvas(UICanvas* canvas) {
    if (canvas == NULL) {
        LOG_E("Engine core: Unregister UI canvas: Canvas is NULL.");
        return;
    }

    if (canvas->event_destroyed != NULL)
        canvas->event_destroyed(canvas);

    for (size_t i = 0; i < canvas->uiComponents.size; i++) {
        void* comp = canvas->uiComponents.items[i];
        if (comp == NULL) {
            LOG_E("Engine core: Unregister UI canvas: Component is NULL at index %d", i);
            continue;
        }

        void (*event_destroyed)(void*, UICanvas*) = *(void (**)(void*, UICanvas*))((char*)comp + sizeof(void (*)(void*, UICanvas*)) * 3);
        if (event_destroyed != NULL)
            event_destroyed(comp, canvas);

        free(comp);
        canvas->uiComponents.items[i] = NULL;
    }

    LOG("Engine core: UI Canvas with ID %d unregistered.", canvas->id);

    LIST_CLEAN(canvas->uiComponents);

    int indexToRemove = LIST_FIND_INDEX(getLevel()->allUICanvases, UICanvas*, , canvas);
    LIST_REMOVE_CLEAN(getLevel()->allUICanvases, UICanvas*, indexToRemove);
}

int engineCore_loadLevel(Level* level) {
    LOG("Requested to load level \"%s\".", level->name);
    getCore()->_loadingLevel = 1;

    if (level->name == NULL) {
        LOG_E("Failed to load level! Level name is NULL.");
        return 0;
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

    LOG("Cleaning UI canvases.");
    _engineCore_cleanUICanvases();

    LOG("Transitioning from \"%s\" to \"%s\"...", getLevel()->name, level->name);
    getCore()->_currentLevel = *level;

    LOG("Initializing new level...");
    LIST_INIT(getLevel()->allGameObjects);
    LIST_INIT(getLevel()->allUICanvases);
    LOG("Level initialized.");

    // Canvas amount
    LOG("UI canvases count: %d", getLevel()->allUICanvases.size);

    LOG("Level \"%s\" loaded successfully.", getLevel()->name);
    getCore()->_loadingLevel = 0;

    if (getLevel()->event_loaded != NULL)
        getLevel()->event_loaded();

    return 1;
}

void engineCore_setInputFocus(InputFocus focus) {
    getCore()->_inputFocus = focus;
}

InputFocus engineCore_getInputFocus() {
    return getCore()->_inputFocus;
}

void engineCore_setFocusedUIComponent(UICanvas* canvas, void* component) {
    getCore()->_focusedUICanvas = canvas;
    getCore()->_focusedUIComponent = component;
}

void* engineCore_getFocusedUIComponent() {
    return getCore()->_focusedUIComponent;
}

UICanvas* engineCore_getFocusedUICanvas() {
    return getCore()->_focusedUICanvas;
}