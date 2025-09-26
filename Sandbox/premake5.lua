project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")


    files { "src/**.cpp", "src/**.h" }


    includedirs {
        "../Pineapple",
    }

    links { "Pineapple" }

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
