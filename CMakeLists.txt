#only for compile commands

cmake_minimum_required(VERSION 3.25)
project(Pineapple LANGUAGES C CXX)

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Platform defines
if(UNIX AND NOT APPLE)
    add_definitions(-DPLATFORM_LINUX)
elseif(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DPLATFORM_MAC)
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/Pineapple-Core/src
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glm
    ${CMAKE_SOURCE_DIR}/vendor/stb_image
    ${CMAKE_SOURCE_DIR}/vendor/imgui
    ${CMAKE_SOURCE_DIR}/vendor/nanodbc
)

# Pineapple-Core sources
file(GLOB_RECURSE CORE_SOURCES
    "Pineapple-Core/src/*.cpp"
    "Pineapple-Core/src/*.h"
)

# External files
set(EXTERNAL_FILES
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/nanodbc/nanodbc/nanodbc.cpp"
)

# Dummy target for clangd
add_library(PineappleCoreDummy STATIC
    ${CORE_SOURCES}
    ${EXTERNAL_FILES}
)

# Include directories for dummy target
target_include_directories(PineappleCoreDummy PRIVATE
    ${CMAKE_SOURCE_DIR}/Pineapple-Core/src
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glm
    ${CMAKE_SOURCE_DIR}/vendor/stb_image
    ${CMAKE_SOURCE_DIR}/vendor/imgui
    ${CMAKE_SOURCE_DIR}/vendor/nanodbc
)

# Compiler options
if(UNIX)
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_C_COMPILER clang)
    add_compile_options(-fcolor-diagnostics -Wall -Wextra -pedantic)
endif()



# Optional: add dummy executable for Pineapple-App if you want
file(GLOB_RECURSE APP_SOURCES
    "Pineapple-App/src/*.cpp"
    "Pineapple-App/src/*.h"
)
add_executable(PineappleAppDummy ${APP_SOURCES})
target_link_libraries(PineappleAppDummy PRIVATE PineappleCoreDummy)
