project(Sandbox LANGUAGES CXX)

add_compile_definitions(GLFW_INCLUDE_NONE)

# Source files
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.h"
)
add_executable(Sandbox ${APP_SOURCES})

# Include directories
target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/src
    ${VENDOR_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(Sandbox PRIVATE Core)
