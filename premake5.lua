-- premake5.lua
workspace "Breaker"
   configurations { "Debug", "Release" }

project "Breaker"
   kind "ConsoleApp" -- WindowedApp
   language "C"
   targetdir "bin/%{cfg.buildcfg}"

   sdl2_includedir = "lib/SDL2/Headers"
   sdl2_libdir = "lib/SDL2"

   files { "**.h", "**.c" }

   filter "system:windows"
      links { "SDL2", "SDL2main" }

   filter "system:linux or system:macosx"
      links { "SDL2" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"