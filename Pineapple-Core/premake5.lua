project "Pineapple-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    defines { "PINEAPPLE_LIB" }


    files {
        "src/**.cpp",
        "src/**.h",
        
        "../vendor/imgui/imgui.cpp",
        "../vendor/imgui/imgui_draw.cpp",
        "../vendor/imgui/imgui_tables.cpp",
        "../vendor/imgui/imgui_widgets.cpp",
        "../vendor/imgui/imgui_demo.cpp",

        "../vendor/imgui/backends/imgui_impl_glfw.cpp",
        "../vendor/imgui/backends/imgui_impl_glfw.h",
        "../vendor/imgui/backends/imgui_impl_opengl3.cpp",
        "../vendor/imgui/backends/imgui_impl_opengl3.h",

        "../vendor/nanodbc/nanodbc/nanodbc.h",
        "../vendor/nanodbc/nanodbc/nanodbc.cpp",

    }

    filter "action:vs*"
        pchheader "pinepch.h"
        pchsource "src/pinepch.cpp"

    filter "action:not vs*"
        pchheader "src/pinepch.h"
    filter{}

    includedirs {
        "src",
        "../vendor/glfw/include",
        "../vendor/glm",
        "../vendor/stb_image",
        "../vendor/imgui",
        "../vendor/nanodbc",
    }
    libdirs {
        "../vendor/glfw/build/src",
    }
    links {
        "glfw3",
    }

    -- Cross-platform linking
    filter "system:windows"
        links { "opengl32", "gdi32", "user32", "shell32" }

    filter "system:linux"
        links { "GL", "dl", "m", "pthread", "X11", "odbc" }

    filter "system:macosx"
        links { "Cocoa.framework", "OpenGL.framework",
         "IOKit.framework", "CoreVideo.framework"}

    filter {}  -- clear filter

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
