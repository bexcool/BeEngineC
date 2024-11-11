rm -rf ./projectTemplate

mkdir -p ./projectTemplate/libs/BeEngine/include
mkdir -p ./projectTemplate/libs/BeEngine/lib
mkdir -p ./projectTemplate/src

cat << EOT >> ./projectTemplate/src/main.c
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
EOT

cp ./src/*.h ./projectTemplate/libs/BeEngine/include

bash ./buildRelease.sh

cp ./bin/Release/libBeEngine.dylib ./projectTemplate/libs/BeEngine/lib/libBeEngine.dylib