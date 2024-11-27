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

   files { "src/**.h", "src/**.c" } -- "src/**.h", 


   filter "system:macosx"
      libdirs {
         "./libs/SDL2/lib",
      }
      includedirs {
         "./libs/SDL2/include",
      }
      links { "SDL2", "SDL2_image", "SDL2_ttf" }
      defines { "SDL_MAIN_HANDLED" }

   filter "configurations:Debug"
      defines { 
         "DEBUG",
         "BEENGINE_VERSION_MAJOR=1", 
         "BEENGINE_VERSION_MINOR=0", 
         "BEENGINE_VERSION_PATCH=0", 
         "BEENGINE_VERSION_BUILD=1" 
      }
      buildoptions { "-fsanitize=address" }
      linkoptions { "-fsanitize=address" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"