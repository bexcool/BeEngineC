#include "BeEngine.h"

void gameEngineInitialized();

int main(int argc, char* argv[]) {
    engineCore_startGameEngine("BeEngine Project Template", argc, argv, &gameEngineInitialized);
}

void gameEngineInitialized() {
    // Load your level here   
}
