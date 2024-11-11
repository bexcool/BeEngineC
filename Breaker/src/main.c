#include <stdio.h>
#include "BeEngine.h"
#include "array.h"
#include "testLevel.h"

void gameEngineInitialized();

int main(int argc, const char* argv[]) {
    EngineOptions options = {
        .projectName = "Breaker (BeEngine)",
        .window_x = 200,
        .window_y = 200,
        .window_width = 800,
        .window_height = 600
    };

    EngineEvents events = {
        .engineInitialized = &gameEngineInitialized
    };
    
    engineCore_startGameEngine(&options, &events, argc, argv);
}

void gameEngineInitialized() {
    _testLevel_initialize();   
}