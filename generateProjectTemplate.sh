#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <Name>"
    exit 1
fi

NAME=$1

rm -rf ./projectTemplate

mkdir -p ./projectTemplate/${NAME}/libs/BeEngine/include
mkdir -p ./projectTemplate/${NAME}/libs/BeEngine/lib
mkdir -p ./projectTemplate/${NAME}/src
mkdir -p ./projectTemplate/${NAME}/include

cat << EOT >> ./projectTemplate/${NAME}/src/main.c
#include "BeEngine.h"
#include "BeEngineUI.h"

void event_gameEngineInitialized();

int main(int argc, char* argv[]) {
    EngineOptions options = {
        .projectName = "BeEngineC Project",
        .window_x = 200,
        .window_y = 200,
        .window_width = 800,
        .window_height = 600
    };

    EngineEvents events = {
        .event_engineInitialized = &event_gameEngineInitialized};

    engineCore_startGameEngine(&options, &events, argc, argv);
}

void event_gameEngineInitialized() {
    // Load your level here   
}
EOT

cat << EOT >> ./projectTemplate/${NAME}/premake5.lua
-- premake5.lua
workspace "${NAME}"
    configurations { "Debug", "Release" }

project "${NAME}"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    architecture "x86_64"  -- Default architecture

    filter "system:macosx"
        architecture "arm64"

    files { "include/**.h", "src/**.c" }

    includedirs {
        "libs/BeEngine/include",
        "libs/SDL2/include"
    }

    libdirs {
        "libs/BeEngine/lib",
        "libs/SDL2/lib"
    }

    links { "SDL2", "SDL2_image", "SDL2_ttf", "BeEngine" }
    defines { "SDL_MAIN_HANDLED" }

    linkoptions { "-rpath", "@executable_path/../../libs/BeEngine/lib" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        buildoptions { "-fsanitize=address" }
        linkoptions { "-fsanitize=address" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
EOT

find ./include -type f -exec cp {} ./projectTemplate/${NAME}/libs/BeEngine/include \;
cp ./premake.sh ./projectTemplate/${NAME}/premake.sh
cp ./buildDebug.sh ./projectTemplate/${NAME}/buildDebug.sh
cp ./buildRelease.sh ./projectTemplate/${NAME}/buildRelease.sh

cp -r ./libs/SDL2 ./projectTemplate/${NAME}/libs/SDL2
cp -r ./scripts ./projectTemplate/${NAME}/scripts

bash ./buildRelease.sh

# Idk zatím jak udělat
#cp -r ./bin/Release/assets ./projectTemplate/${NAME}/bin/

cp ./bin/Release/libBeEngine.dylib ./projectTemplate/${NAME}/libs/BeEngine/lib/libBeEngine.dylib