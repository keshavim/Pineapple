project(Pineapple-Core LANGUAGES CXX)

# Source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.h
)


# Create static library
add_library(Pineapple-Core STATIC ${SOURCES})

# Include directories
target_include_directories(Pineapple-Core PUBLIC
    src # project headers
    ${VENDOR_INCLUDE} # vendor headers (covers imgui/imgui.h)
    ${VENDOR_IMGUI_INCLUDE} # covers direct "imgui.h" includes
)

# Precompiled headers (optional)
if(MSVC)
    target_precompile_headers(Pineapple-Core PRIVATE src/pinepch.h)
endif()



if(WIN32)
    set(IMGUI_LIB "imgui.lib")
    set(NANODBC_LIB "nanodbc.lib")
    set(GLFW3_LIB "glfw3.lib")
elseif(UNIX)
    set(IMGUI_LIB "libimgui.a")
    set(NANODBC_LIB "libnanodbc.a")
    set(GLFW3_LIB "libglfw3.a")
endif()


# ImGui
add_library(imgui_lib STATIC IMPORTED)
set_target_properties(imgui_lib PROPERTIES
    IMPORTED_LOCATION "${VENDOR_LIB_DIR}/${IMGUI_LIB}"
    IMPORTED_NO_SONAME TRUE
)

# nanodbc
add_library(nanodbc_lib STATIC IMPORTED)
set_target_properties(nanodbc_lib PROPERTIES
    IMPORTED_LOCATION "${VENDOR_LIB_DIR}/${NANODBC_LIB}"
    IMPORTED_NO_SONAME TRUE
)

# glfw3
add_library(glfw3_lib STATIC IMPORTED)
set_target_properties(glfw3_lib PROPERTIES
    IMPORTED_LOCATION "${VENDOR_LIB_DIR}/${GLFW3_LIB}"
    IMPORTED_NO_SONAME TRUE
)

# Link imported targets into Pineapple-Core (these will propagate to the final exe)
target_link_libraries(Pineapple-Core PRIVATE
    imgui_lib
    nanodbc_lib
    glfw3_lib
)

# Platform-specific libraries
if(WIN32)
    target_link_libraries(Pineapple-Core PRIVATE
        opengl32
        gdi32
        user32
        shell32
    )
elseif(UNIX AND NOT APPLE)
    target_link_libraries(Pineapple-Core PRIVATE
        GL
        dl
        m
        pthread
        X11
        wayland-client
        odbc
    )
elseif(APPLE)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(COREVIDEO_FRAMEWORK CoreVideo)
    find_library(OPENGL_FRAMEWORK OpenGL)
    target_link_libraries(Pineapple-Core PRIVATE
        ${COCOA_FRAMEWORK}
        ${IOKIT_FRAMEWORK}
        ${COREVIDEO_FRAMEWORK}
        ${OPENGL_FRAMEWORK}
    )
endif()

# Compile definitions
target_compile_definitions(Pineapple-Core PUBLIC PINEAPPLE_LIB)
