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



# ===============================
# Vendor library filenames
# ===============================
if(WIN32)
    set(IMGUI_LIB "imgui.lib")
    set(MARIADB_LIB "mariadbcpp.dll")
    set(GLFW3_LIB "glfw3.lib")
elseif(APPLE)
    set(IMGUI_LIB "libimgui.a")
    set(MARIADB_LIB "libmariadbcpp.dylib")  # macOS uses .dylib
    set(GLFW3_LIB "libglfw3.a")
else() # Linux/other UNIX
    set(IMGUI_LIB "libimgui.a")
    set(MARIADB_LIB "libmariadbcpp.so")
    set(GLFW3_LIB "libglfw3.a")
endif()

# ===============================
# Imported vendor libraries
# ===============================
add_library(imgui_lib STATIC IMPORTED)
set_target_properties(imgui_lib PROPERTIES
    IMPORTED_LOCATION "${VENDOR_LIB_DIR}/${IMGUI_LIB}"
    IMPORTED_NO_SONAME TRUE
)

add_library(mariadb_lib SHARED IMPORTED)
set_target_properties(mariadb_lib PROPERTIES
    IMPORTED_LOCATION "${VENDOR_LIB_DIR}/${MARIADB_LIB}"
    IMPORTED_NO_SONAME TRUE
)

add_library(glfw3_lib STATIC IMPORTED)
set_target_properties(glfw3_lib PROPERTIES
    IMPORTED_LOCATION "${VENDOR_LIB_DIR}/${GLFW3_LIB}"
    IMPORTED_NO_SONAME TRUE
)

# ===============================
# Link vendor libraries into Pineapple-Core
# ===============================
target_link_libraries(Pineapple-Core PRIVATE
    imgui_lib
    mariadb_lib
    glfw3_lib
)

# ===============================
# Platform-specific dependencies
# ===============================
if(WIN32)
    target_link_libraries(Pineapple-Core PRIVATE
        opengl32
        gdi32
        user32
        shell32
    )
elseif(APPLE)
    # Only needed for macOS frameworks
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
else() # Linux
    # Only essential libraries for MariaDB and OpenGL
    target_link_libraries(Pineapple-Core PRIVATE
        GL
        dl
        m
        pthread
        X11
    )
endif()


# Compile definitions
target_compile_definitions(Pineapple-Core PUBLIC PINEAPPLE_LIB)
