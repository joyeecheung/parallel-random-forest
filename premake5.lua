-- premake5.lua
solution "RandomForest"
   configurations { "Debug", "Release", "clang" }

   -- A project defines one build target
   project "RandomForest"
      kind "ConsoleApp"
      language "C++"
      files { "src/*.cpp" }
      includedirs { "src" }

      configuration { "gmake", "-std=c++11" }
        buildoptions { "-fopenmp" }
        links { "gomp" }

      configuration { "vs*" }
        buildoptions { "/openmp" }   

      configuration "Debug"
         defines { "DEBUG" } -- -DDEBUG
         flags { "Symbols" }

      configuration "Release"
         defines { "NDEBUG" } -- -NDEBUG
         flags { "Optimize" }

      configuration "clang"
         toolset "clang"
