
project(Core LANGUAGES CXX)


if(UNIX AND NOT APPLE) # Linux only
    set(CMAKE_C_COMPILER "gcc" CACHE STRING "C compiler" FORCE)
    set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler" FORCE)
endif()

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # GCC-specific flags for better warnings and errors
    add_compile_options(
        -Wall # Enable all standard warnings
        -Wextra # Extra warnings
        -Wpedantic # Strict standard compliance
        -fdiagnostics-color=always # Colorized diagnostics
        -fdiagnostics-show-option # Show which warning flag triggered it
    )
endif()

if(WIN32)
    add_compile_definitions(PAP_PLATFORM_WINDOWS)
elseif(APPLE)
    add_compile_definitions(PAP_PLATFORM_MAC)
elseif(UNIX)
    add_compile_definitions(PAP_PLATFORM_LINUX)
endif()


add_compile_definitions(
    $<$<CONFIG:Debug>:PAP_DEBUG>
    $<$<CONFIG:Release>:PAP_RELEASE>
)



add_compile_definitions(GLFW_INCLUDE_NONE)

# Source files (recursive to include subdirectories)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.h"
)
add_library(Core STATIC ${SOURCES})

# Explicitly set output name to ensure consistency
set_target_properties(Core PROPERTIES OUTPUT_NAME "Core")

# Include directories
target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${VENDOR_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(Core PRIVATE
    ${VENDOR_LIBRARIES}
)

# # Platform-specific libraries
if(WIN32)
    target_link_libraries(Core PRIVATE opengl32 gdi32 user32 shell32)
elseif(APPLE)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(COREVIDEO_FRAMEWORK CoreVideo)
    find_library(OPENGL_FRAMEWORK OpenGL)
    target_link_libraries(Core PRIVATE
        ${COCOA_FRAMEWORK}
        ${IOKIT_FRAMEWORK}
        ${COREVIDEO_FRAMEWORK}
        ${OPENGL_FRAMEWORK}
    )
else()
    target_link_libraries(Core PRIVATE GL dl m pthread X11)
endif()
