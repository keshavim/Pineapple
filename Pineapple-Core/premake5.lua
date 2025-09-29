project "Pineapple-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    defines { "PINEAPPLE_LIB" }


    files { "src/**.cpp", "src/**.h", "include/**.h"}

    filter "action:vs*"
        pchheader "pinepch.h"
        pchsource "src/pinepch.cpp"

    filter "action:not vs*"
        pchheader "src/pinepch.h"
    filter{}

    includedirs {
        "include",
        "../vendor/glfw/include"
    }
    libdirs {
        "../vendor/glfw/build/src"
    }

    -- Cross-platform linking
    filter "system:windows"
        links { "glfw3", "opengl32", "gdi32", "user32", "shell32" }

    filter "system:linux"
        links { "glfw3", "GL", "dl", "m", "pthread", "X11" }

    filter "system:macosx"
        links { "glfw3", "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework" }

    filter {}  -- clear filter

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
