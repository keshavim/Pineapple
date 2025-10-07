project(Sandbox LANGUAGES CXX)

# Source files
file(GLOB_RECURSE APP_SOURCES
    "src/*.cpp"
    "src/*.h"
)
add_executable(Sandbox ${APP_SOURCES})

# Include directories
target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/src
)

# Link libraries
target_link_libraries(Sandbox PRIVATE Core)
