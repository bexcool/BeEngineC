-- premake5.lua
workspace "TestGame"
    configurations { "Debug", "Release" }

project "TestGame"
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
