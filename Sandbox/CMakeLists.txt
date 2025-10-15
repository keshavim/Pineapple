project(Sandbox LANGUAGES CXX)




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
