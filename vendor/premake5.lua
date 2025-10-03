-- Determine copy commands based on OS
local function copy_dir(src, dst)
    if os.host() == "windows" then
        return "{COPYDIR} " .. src .. " " .. dst
    else
        return "cp -r " .. src .. " " .. dst
    end
end

local function copy_files(src_pattern, dst)
    if os.host() == "windows" then
        return "{COPYFILES} " .. src_pattern .. " " .. dst
    else
        return "cp " .. src_pattern .. " " .. dst
    end
end



VENDOR_DIR = "../vendor"
BUILD_DIR  = "../build_vendor"
INCLUDE_DIR = VENDOR_DIR .. "/include"
LIB_DIR = VENDOR_DIR .. "/libs"


os.execute("{MKDIR} " .. BUILD_DIR)
os.execute("{MKDIR} " .. INCLUDE_DIR)
os.execute("{MKDIR} " .. LIB_DIR)


-- =======================================
-- GLFW
-- =======================================
os.execute("cmake " .. VENDOR_DIR .. "/glfw -B" .. BUILD_DIR .. "/glfw_build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF")
os.execute("cmake --build " .. BUILD_DIR .. "/glfw_build --config Release")
os.execute("{COPYDIR} " .. VENDOR_DIR .. "/glfw/include/GLFW", INCLUDE_DIR)
os.execute("{COPYFILES}" .. BUILD_DIR .. "/glfw_build/src/*.a", LIB_DIR)

-- =======================================
-- nanodbc
-- =======================================
os.execute("cmake " .. VENDOR_DIR .. "/nanodbc -B" .. BUILD_DIR .. "/nanodbc_build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DNANODBC_BUILD_EXAMPLES=OFF -DNANODBC_BUILD_TESTS=OFF -DNANODBC_DISABLE_ASYNC=ON")
os.execute("cmake --build " .. BUILD_DIR .. "/nanodbc_build --config Release")
os.execute("{MKDIR} " .. INCLUDE_DIR .. "/nanodbc")
os.execute("{COPYFILES}" .. VENDOR_DIR .. "/nanodbc/nanodbc/*.h", INCLUDE_DIR .. "/nanodbc")
os.execute("{COPYFILES}" .. BUILD_DIR .. "/nanodbc_build/*.a", LIB_DIR)


workspace "build vendor"
    configurations { "Release" }

    -- ImGui project (compile manually)
project "imgui"
    kind "StaticLib"
    language "C++"
    architecture "x64"
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
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imstb_textedit.h " .. INCLUDE_DIR .. "/imgui/imstb_textedit.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imstb_truetype.h " .. INCLUDE_DIR .. "/imgui/imstb_truetype.h",


        -- Create backends folder
        "{MKDIR} " .. INCLUDE_DIR .. "/imgui/backends",
        -- Copy backend headers
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/backends/imgui_impl_glfw.h " .. INCLUDE_DIR .. "/imgui/backends/imgui_impl_glfw.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/backends/imgui_impl_opengl3.h " .. INCLUDE_DIR .. "/imgui/backends/imgui_impl_opengl3.h"
    }

    filter "configurations:Release"
        optimize "On"
