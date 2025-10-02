project "Pineapple-App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir (outputdir)
    objdir (outputdir_obj)


    files { "src/**.cpp", "src/**.h" }

    includedirs {
        "../Pineapple-Core/src",
        "../vendor/stb_image",
        "../vendor/imgui",
        "../vendor/nanodbc",
        "../vendor/glfw"
    }


    links { "Pineapple-Core"}


    filter "system:linux"
        libdirs {
            "../vendor/glfw"
        }
        links { "glfw3", "GL", "dl", "m", "pthread", "X11", "odbc", "wayland-client" }

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
