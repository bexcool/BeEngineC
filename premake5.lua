-- premake5.lua
workspace "BeEngineC"
   configurations { "Debug", "Release" }
   platforms { "x64", "x86_64", "ARM" }

   if _ACTION == "vs2022" then
      location ""
      toolset "msc-v143"
   end

project "BeEngineC"
   kind "SharedLib" -- WindowedApp / ConsoleApp
   language "C"
   targetdir "bin/%{cfg.buildcfg}/%{cfg.platform}"

   -- Set architecture
   filter "platforms:x86_64"
      architecture "x86_64"

   filter "platforms:ARM"
      architecture "ARM"

   filter "system:windows"
      defines { "BUILD_DLL" }

   files { "include/**.h", "src/**.c" } -- "src/**.h", 

   vpaths {
      ["Header Files/*"] = { "include/**.h" },
      ["Source Files/*"] = { "src/**.c" }
   }

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

   links { "SDL2", "SDL2_image", "SDL2_ttf", "SDL2_mixer" }

   defines {
         "BEENGINE_VERSION_MAJOR=1", 
         "BEENGINE_VERSION_MINOR=0", 
         "BEENGINE_VERSION_PATCH=0", 
         "BEENGINE_VERSION_BUILD=1",
         "SDL_MAIN_HANDLED"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

   -- Specific for gmake2
   if _ACTION == "gmake2" then
      filter {"system:macosx", "configurations:Debug"}
         buildoptions { "-fsanitize=address" }
         linkoptions { "-fsanitize=address" }
   end