-- premake5.lua
workspace "Breaker"
   configurations { "Debug", "Release" }

project "Breaker"
   kind "ConsoleApp" -- WindowedApp / ConsoleApp
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   architecture "x86_64"  -- Default architecture

   filter "system:macosx"
      architecture "arm64"

   files { "src/**.h", "src/**.c" } -- "src/**.h", 

   includedirs {
      "libs/BeEngine/include"
   }

   libdirs {
      "libs/BeEngine/lib"
   }

   filter "system:macosx"
      links { "BeEngine" }
      linkoptions { "-rpath", "@executable_path/../../libs/BeEngine/lib" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      buildoptions { "-fsanitize=address" }
      linkoptions { "-fsanitize=address" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"