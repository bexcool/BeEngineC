#include "BeEngine.h"

void gameEngineInitialized();

int main(int argc, char* argv[]) {
    EngineOptions options = {
        .projectName = "BeEngine Project",
        .window_x = 200,
        .window_y = 200,
        .window_width = 800,
        .window_height = 600
    };

    EngineEvents events = {
        .engineInitialized = &gameEngineInitialized
    };
    
    engineCore_startGameEngine(options, events, argc, argv);
}

void gameEngineInitialized() {
    // Load your level here   
}