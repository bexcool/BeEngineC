-- premake5.lua
workspace "BeEngine"
   configurations { "Debug", "Release" }

project "BeEngine"
   kind "SharedLib" -- WindowedApp / ConsoleApp
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   architecture "x86_64"  -- Default architecture

   filter "system:macosx"
      architecture "arm64"

   files { "include/**.h", "src/**.c" } -- "src/**.h", 

   libdirs {
      "libs/SDL2/lib",
   }
   includedirs {
      "libs/SDL2/include",
      "include",
      "include/ui",
      "include/ui/components",
      "include/components"
   }
   links { "SDL2", "SDL2_image", "SDL2_ttf" }
   defines { "SDL_MAIN_HANDLED" }

   defines {
         "BEENGINE_VERSION_MAJOR=1", 
         "BEENGINE_VERSION_MINOR=0", 
         "BEENGINE_VERSION_PATCH=0", 
         "BEENGINE_VERSION_BUILD=1" 
   }

   filter "configurations:Debug"
      defines { 
         "DEBUG"
      }
      buildoptions { "-fsanitize=address" }
      linkoptions { "-fsanitize=address" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"