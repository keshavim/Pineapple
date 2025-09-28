project "Pineapple"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    defines { "PINEAPPLE_LIB" }


    files { "src/**.cpp", "src/**.h", "include/**.h"}

    filter "action:vs*"
        pchheader "pinepch.h"
        pchsource "pinepch.cpp"

    filter "action:not vs*"
        pchheader "src/pinepch.h"

    includedirs {
        "include"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "configurations:Dist"
        defines { "DIST" }
        optimize "On"
    filter{}
