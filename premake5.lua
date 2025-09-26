require "premake-ninja/ninja"
require "premake-ecc/ecc"

workspace "Pineapple"
    architecture "x86_64"
    configurations { "Debug", "Release", "Dist" }
    startproject "App"
    location "build"

    include "vendor"


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

    buildcommands {"clangd"}

    
