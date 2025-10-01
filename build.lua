workspace "Pineapple"
    architecture "x86_64"
    startproject "Pineapple-App"
    configurations { "Debug", "Release", "Dist" }
    location "build"

    --compile venders with their own build systems
    include "build_external"

    flags = {
        gcc_clang = {
            "-Wall",
            "-Wextra",
            "-pedantic",
        },
        msvc = {
            "/W4",           
        }
    }

    -- Setting up toolsets per platform
    filter "system:linux"
        toolset "gcc"
        defines { "PLATFORM_LINUX" }
        buildoptions(flags.gcc_clang)

    filter "system:windows"
        toolset "v143"
        defines  { "PLATFORM_WINDOWS" }
        buildoptions(flags.msvc)

    filter "system:macosx"
        toolset "clang"
        defines( "PLATFORM_MAC" )
        buildoptions(flags.gcc_clang)

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "DIST" }
        optimize "On"
    filter{}



    include "Pineapple-Core"
    include "Pineapple-App"
