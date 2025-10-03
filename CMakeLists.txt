cmake_minimum_required(VERSION 3.25)
project(Pineapple LANGUAGES C CXX)

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



# -------------------------
# Global vendor paths (use CACHE so subdirs can see them)
# -------------------------
set(VENDOR_DIR           ${CMAKE_CURRENT_SOURCE_DIR}/vendor           CACHE INTERNAL "")
set(VENDOR_INCLUDE       ${VENDOR_DIR}/include                       CACHE INTERNAL "")
set(VENDOR_IMGUI_INCLUDE ${VENDOR_DIR}/include/imgui                 CACHE INTERNAL "")
set(VENDOR_LIB_DIR       ${VENDOR_DIR}/libs                          CACHE INTERNAL "")


# Output directories
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# Platform defines
if(UNIX AND NOT APPLE)
    add_definitions(-DPLATFORM_LINUX)
elseif(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DPLATFORM_MAC)
endif()



# Add subprojects
add_subdirectory(Pineapple-Core)
add_subdirectory(Pineapple-App)
