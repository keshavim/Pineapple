project(Pineapple-App LANGUAGES CXX)

# App sources
file(GLOB_RECURSE APP_SOURCES src/*.cpp src/*.h)

# Create executable
add_executable(Pineapple-App ${APP_SOURCES})

# Include directories
target_include_directories(Pineapple-App PRIVATE
    ../Pineapple-Core/src
    ../vendor/include
    ../vendor/include/imgui
    ../vendor/stb_image
)

# Link Pineapple-Core
target_link_libraries(Pineapple-App PRIVATE Pineapple-Core)
