project(Pineapple-App LANGUAGES CXX)

# App sources
file(GLOB_RECURSE APP_SOURCES src/*.cpp src/*.h)

# Create executable
add_executable(Pineapple-App ${APP_SOURCES})

# Include directories
target_include_directories(Pineapple-App PRIVATE
    ${CMAKE_SOURCE_DIR}/Pineapple-Core/src
    ${CMAKE_SOURCE_DIR}/vendor/include
    ${CMAKE_SOURCE_DIR}/vendor/include/imgui
    ${CMAKE_SOURCE_DIR}/vendor/stb_image
)

# Link Pineapple-Core
target_link_libraries(Pineapple-App PRIVATE Pineapple-Core)
