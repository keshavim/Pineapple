project "Pineapple-App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir (outputdir)
    objdir (outputdir_obj)


    files { "src/**.cpp", "src/**.h" }

    includedirs {
        "../Pineapple-Core/src",
        "../vendor/glfw/include",
        "../vendor/imgui",
    }
    libdirs {
        "../vendor/glfw/build/src",
    }

    links { "Pineapple-Core", "glfw3" }

    -- Cross-platform linking
    filter "system:windows"
        links { "opengl32", "gdi32", "user32", "shell32" }

    filter "system:linux"
        links { "GL", "dl", "m", "pthread", "X11", "odbc" }

    filter "system:macosx"
        links { "Cocoa.framework", "OpenGL.framework",
         "IOKit.framework", "CoreVideo.framework" }
