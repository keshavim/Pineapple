cmake_minimum_required(VERSION 3.27)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_SUPPORT OFF)

project(Pineapple LANGUAGES C CXX)

# -------------------------
# C++ Standard
# -------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------
# Output directories
# -------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

# -------------------------
# Vendor subproject
# -------------------------
add_subdirectory(vendor)

# -------------------------
# Add main subprojects
# -------------------------
add_subdirectory(Core)
add_subdirectory(Sandbox)
