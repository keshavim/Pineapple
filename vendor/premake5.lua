-- Determine copy commands based on OS

workspace "build vendor"
    configurations { "Release" }

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
local GLFW_LIB = BUILD_DIR .. "/glfw_build/src/libglfw3.a"
if not os.isfile(GLFW_LIB) then
    os.execute("cmake " .. VENDOR_DIR .. "/glfw -B" .. BUILD_DIR .. "/glfw_build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF")
    os.execute("cmake --build " .. BUILD_DIR .. "/glfw_build --config Release")
    os.execute("{COPYDIR} " .. VENDOR_DIR .. "/glfw/include/GLFW " .. INCLUDE_DIR)

    if os.host() == "windows" then
        os.execute("xcopy /Y /I \"" .. BUILD_DIR .. "\\glfw_build\\src\\*.a\" \"" .. LIB_DIR .. "\\\"")
    else
        os.execute("cp -v " .. BUILD_DIR .. "/glfw_build/src/*.a " .. LIB_DIR)
    end
else
    print("GLFW already built. Skipping build.")
end

-- =======================================
-- MariaDB Connector/C++
-- =======================================
local MARIADB_DIR = VENDOR_DIR .. "/mariadbc"
local MARIADB_BUILD_DIR = BUILD_DIR .. "/mariadb_build"
local MARIADB_INCLUDE_DIR = INCLUDE_DIR .. "/mariadbc"

local function mariadbLibExists()
    if os.host() == "windows" then
        return os.isfile(MARIADB_BUILD_DIR .. "/Release/mariadb.dll")
    elseif os.host() == "macosx" then
        return os.isfile(MARIADB_BUILD_DIR .. "/libmariadb.dylib")
    else
        return os.isfile(MARIADB_BUILD_DIR .. "/libmariadb.so")
    end
end

if not os.isdir(MARIADB_BUILD_DIR) then
    os.execute("cmake " .. MARIADB_DIR ..
        " -B" .. MARIADB_BUILD_DIR ..
        " -DCMAKE_BUILD_TYPE=Release" ..
        " -DBUILD_SHARED_LIBS=ON" ..
        " -DWITH_SSL=OFF" ..
        " -DWITH_UNIT_TESTS=OFF" ..
        " -DWITH_EXAMPLES=OFF" ..
        " -DCMAKE_POLICY_VERSION_MINIMUM=3.5")
    os.execute("cmake --build " .. MARIADB_BUILD_DIR .. " --config Release")
    os.execute("{COPYDIR} " .. MARIADB_DIR .. "/include/ " .. INCLUDE_DIR)
    os.rename(INCLUDE_DIR .. "/include", INCLUDE_DIR .. "/mariadbc")
elseif mariadbLibExists() then
    -- Copy shared library per platform
    if os.host() == "windows" then
        os.execute("xcopy /Y /I \"" .. MARIADB_BUILD_DIR .. "\\Release\\*.dll\" \"" .. LIB_DIR .. "\\\"")
    elseif os.host() == "macosx" then
        os.execute("cp -v " .. MARIADB_BUILD_DIR .. "/*.dylib " .. LIB_DIR)
    else
        os.execute("cp -v " .. MARIADB_BUILD_DIR .. "/*.so " .. LIB_DIR)
    end
    print("MariaDB build already exists. Skipping build.")
end

-- =======================================
-- ImGui project (compile manually)
-- =======================================
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

    postbuildcommands {
        "{MKDIR} " .. INCLUDE_DIR .. "/imgui",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imgui.h " .. INCLUDE_DIR .. "/imgui/imgui.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imconfig.h " .. INCLUDE_DIR .. "/imgui/imconfig.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imgui_internal.h " .. INCLUDE_DIR .. "/imgui/imgui_internal.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imstb_rectpack.h " .. INCLUDE_DIR .. "/imgui/imstb_rectpack.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imstb_textedit.h " .. INCLUDE_DIR .. "/imgui/imstb_textedit.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/imstb_truetype.h " .. INCLUDE_DIR .. "/imgui/imstb_truetype.h",
        "{MKDIR} " .. INCLUDE_DIR .. "/imgui/backends",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/backends/imgui_impl_glfw.h " .. INCLUDE_DIR .. "/imgui/backends/imgui_impl_glfw.h",
        "{COPYFILE} " .. VENDOR_DIR .. "/imgui/backends/imgui_impl_opengl3.h " .. INCLUDE_DIR .. "/imgui/backends/imgui_impl_opengl3.h"
    }

    filter "configurations:Release"
        optimize "On"
