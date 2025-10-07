cmake_minimum_required(VERSION 4.0) # Updated to a more modern version
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_SUPPORT OFF)

project(Pineapple LANGUAGES C CXX)

# -------------------------
# C++ Standard
# -------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler-specific flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # GCC-specific flags for better warnings and errors
    add_compile_options(
        -Wall              # Enable all standard warnings
        -Wextra            # Extra warnings
        -Wpedantic         # Strict standard compliance
        -fdiagnostics-color=always        # Colorized diagnostics
        -fdiagnostics-show-option         # Show which warning flag triggered it
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
add_subdirectory(Pineapple-Core)
add_subdirectory(Pineapple-App)
