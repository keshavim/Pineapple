workspace "VendorBuild"
    architecture "x64"
    startproject "BuildVendor"
    configurations { "Debug", "Release" }

VENDOR_DIR = "../vendor"
BUILD_DIR  = "../build_vendor"
INCLUDE_DIR = VENDOR_DIR .. "/include"
LIB_DIR = VENDOR_DIR .. "/libs"

-- Utility project to run all builds
project "BuildVendor"
    kind "Utility"
    language "C++"

    -- Make sure folders exist
    prebuildcommands {
        "{MKDIR} " .. BUILD_DIR,
        "{MKDIR} " .. INCLUDE_DIR,
        "{MKDIR} " .. LIB_DIR
    }

-- GLFW project (build with CMake)
project "GLFW"
    kind "Utility"
    language "C++"
    postbuildcommands {
        "cmake " .. VENDOR_DIR .. "/glfw -B" .. BUILD_DIR .. "/glfw_build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF",
        "cmake --build " .. BUILD_DIR .. "/glfw_build --config Release",
        "{COPYDIR} " .. VENDOR_DIR .. "/glfw/include " .. INCLUDE_DIR .. "/GLFW",
        "{COPYFILES} " .. BUILD_DIR .. "/glfw_build/*.a " .. LIB_DIR
    }

-- nanodbc project (build with CMake)
project "nanodbc"
    kind "Utility"
    language "C++"
    postbuildcommands {
        "cmake " .. VENDOR_DIR .. "/nanodbc -B" .. BUILD_DIR .. "/nanodbc_build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DNANODBC_DISABLE_TESTS=ON -DNANODBC_DISABLE_EXAMPLES=ON -DNANODBC_DISABLE_INSTALL=ON -DNANODBC_DISABLE_ASYNC=ON",
        "cmake --build " .. BUILD_DIR .. "/nanodbc_build --config Release",
        "{COPYDIR} " .. VENDOR_DIR .. "/nanodbc/nanodbc " .. INCLUDE_DIR .. "/nanodbc",
        "{COPYFILES} " .. BUILD_DIR .. "/nanodbc_build/*.a " .. LIB_DIR
    }

    -- ImGui project (compile manually)
project "ImGui"
    kind "StaticLib"
    language "C++"
    targetdir (LIB_DIR)
    objdir (BUILD_DIR .. "/imgui_obj")

    files {
        VENDOR_DIR .. "/imgui/imgui.cpp",
        VENDOR_DIR .. "/imgui/imgui_draw.cpp",
        VENDOR_DIR .. "/imgui/imgui_tables.cpp",
        VENDOR_DIR .. "/imgui/imgui_widgets.cpp",
        VENDOR_DIR .. "/imgui/imgui_demo.cpp",
        VENDOR_DIR .. "/imgui/backends/imgui_impl_glfw.cpp",
        VENDOR_DIR .. "/imgui/backends/imgui_impl_opengl3.cpp",
        VENDOR_DIR .. "/imgui/imgui.h",
        VENDOR_DIR .. "/imgui/backends/imgui_impl_glfw.h",
        VENDOR_DIR .. "/imgui/backends/imgui_impl_opengl3.h"
    }

    includedirs {
        VENDOR_DIR .. "/imgui"
    }

    -- After build, copy headers to vendor/include
    postbuildcommands {
        -- Create main imgui include folder
        "{MKDIR} " .. INCLUDE_DIR .. "/imgui",
        -- Copy only imgui.h
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imgui.h " .. INCLUDE_DIR .. "/imgui/imgui.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imconfig.h " .. INCLUDE_DIR .. "/imgui/imconfig.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imgui_internal.h " .. INCLUDE_DIR .. "/imgui/imgui_internal.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imstb_rectpack.h " .. INCLUDE_DIR .. "/imgui/imstb_rectpack.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imgstb_textedit.h " .. INCLUDE_DIR .. "/imgui/imgstb_textedit.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imstb_truetype.h " .. INCLUDE_DIR .. "/imgui/imstb_truetype.h",


        -- Create backends folder
        "{MKDIR} " .. INCLUDE_DIR .. "/imgui/backends",
        -- Copy backend headers
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/backends/imgui_impl_glfw.h " .. INCLUDE_DIR .. "/imgui/backends/imgui_impl_glfw.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/backends/imgui_impl_opengl3.h " .. INCLUDE_DIR .. "/imgui/backends/imgui_impl_opengl3.h"
    }

    filter "configurations:Release"
        optimize "On"
