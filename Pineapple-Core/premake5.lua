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

