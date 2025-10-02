workspace "Pineapple"
    architecture "x64"
    startproject "Pineapple-App"
    configurations { "Debug", "Release", "Dist" }
    location "build"

    --check external packages
    include "build_external"

    flags = {
        gcc_clang = {
            "-Wall",
            "-Wextra",
            "-pedantic",
            "-fcolor-diagnostics",
            "-fdiagnostics-show-option",
            "-fdiagnostics-format=clang",
            "-fdiagnostics-show-line-numbers",
        },
        msvc = {
            "/W4",
        }
    }

    -- Setting up toolsets per platform
    filter "system:linux"
        toolset "clang"
        defines { "PAP_PLATFORM_LINUX" }
        buildoptions(flags.gcc_clang)

    filter "system:windows"
        toolset "v143"
        defines  { "PAP_PLATFORM_WINDOWS" }
        buildoptions(flags.msvc)

    filter "system:macosx"
        toolset "clang"
        defines( "PAP_PLATFORM_MAC" )
        buildoptions(flags.gcc_clang)

    filter {}


    outputdir = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    outputdir_obj = "%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    include "Pineapple-Core"
    include "Pineapple-App"
