set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_SUPPORT OFF)
project(Pineapple-App LANGUAGES CXX)

# Source files
file(GLOB_RECURSE APP_SOURCES
    "src/*.cpp"
    "src/*.h"
)
add_executable(Pineapple-App ${APP_SOURCES})

# Include directories
target_include_directories(Pineapple-App PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../Pineapple-Core/src
)

# Link libraries
target_link_libraries(Pineapple-App PRIVATE Pineapple-Core)
