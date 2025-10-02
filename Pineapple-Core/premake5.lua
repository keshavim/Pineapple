project "Pineapple-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    targetdir (outputdir)
    objdir (outputdir_obj)
    defines { "PINEAPPLE_LIB" }


    files {
        "src/**.cpp",
        "src/**.h",
    }

    --adding the imgui and nanodbc files
    files(external_files)

    filter "action:vs*"
        pchheader "pinepch.h"
        pchsource "src/pinepch.cpp"

    filter "action:not vs*"
        pchheader "src/pinepch.h"
    filter{}

    includedirs {
        "src",
        "../vendor/stb_image",
        "../vendor/imgui",
        "../vendor/nanodbc",
        "../vendor/glfw"
    }
    libdirs {
        "../vendor/glfw"
    }


    -- Cross-platform linking(only linux for now)
    -- filter "system:windows"
    --     links { "opengl32", "gdi32", "user32", "shell32", "glfw3", }

    filter "system:linux"
        links { "GL", "dl", "m", "pthread", "X11", "odbc", "glfw3", "wayland-client" }

    -- filter "system:macosx"
    --     links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework", "glfw", }


    filter "configurations:Debug"
        defines { "PAP_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "PAP_RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        kind "WindowedApp"
        defines { "PAP_DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
    filter{}
