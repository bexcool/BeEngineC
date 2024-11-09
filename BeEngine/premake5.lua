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

   includedirs {
      "libs/SDL2/include"
   }

   libdirs {
      "libs/SDL2/lib"
   }

   filter "system:macosx"
      links { "SDL2" }
      defines { "SDL_MAIN_HANDLED" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"