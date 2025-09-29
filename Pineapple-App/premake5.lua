project "Pineapple-App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")


    files { "src/**.cpp", "src/**.h", "src/**.hpp", "src/**.cxx" }

    includedirs {
        "../Pineapple-Core/include",
        "../vendor/glfw/include"
    }
    libdirs {
        "../vendor/glfw/build/src"
    }

    links { "Pineapple-Core" }

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
