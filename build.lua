workspace "Pineapple"
    architecture "x86_64"
    startproject "Pineapple-App"
    configurations { "Debug", "Release", "Dist" }
    location "build"

    --compile venders with their own build systems
    include "vendor"

    --seting up toolsets
    filter "system:linux"
        toolset "gcc"
        defines {"PLATFORM_LINUX"}
        buildoptions { "-Wall", "-Wextra", "-pedantic", "--std=c++23" }
    filter "system:windows"
        toolset "v143"
        defines {"PLATFORM_WINDOWS"}
        buildoptions { "/W4" }
    filter "system:macosx"
        toolset "clang"
        defines {"PLATFORM_MAC"}
        buildoptions { "-Wall", "-Wextra", "-pedantic" }

    filter{}



    include "Pineapple-Core"
    include "Pineapple-App"
