require "vendor/premake/premake-ninja/ninja"
require "vendor/premake/premake-ecc/ecc"

workspace "Pineapple"
    architecture "x86_64"
    configurations { "Debug", "Release", "Dist" }
    startproject "App"
    location "build"

    --compile venders with their own build systems
    include "vendor"

    --seting up toolsets
    filter "system:linux"
        toolset "gcc"
        defines {"PLATFORM_LINUX"}
        buildoptions { "-Wall", "-Wextra", "-pedantic" }
    filter "system:windows"
        toolset "v143"
        defines {"PLATFORM_WINDOWS"}
        buildoptions { "/W4" }
    filter "system:macosx"
        toolset "clang"
        defines {"PLATFORM_MAC"}
        buildoptions { "-Wall", "-Wextra", "-pedantic" }

    filter{}



    include "Pineapple"
    include "Sandbox"
