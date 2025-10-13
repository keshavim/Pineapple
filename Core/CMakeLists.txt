
project(Core LANGUAGES CXX)




# Source files (recursive to include subdirectories)
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
    "${VENDOR_DIR}/glad/src/glad.c"
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

# Platform-specific libraries
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
