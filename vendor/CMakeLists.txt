
# -------------------------
# C++ Standard (inherit from parent)
# -------------------------
set(CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------------------------
# Paths
# -------------------------
set(VENDOR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# -------------------------
# GLFW
# -------------------------
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

# -------------------------
# MariaDB Connector/C++
# -------------------------
set(WITH_SSL OFF CACHE BOOL "" FORCE)
set(WITH_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

add_subdirectory(mariadbc)

# -------------------------
# ImGui
# -------------------------
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_SUPPORT OFF)
file(GLOB IMGUI_SRC
    ${VENDOR_INCLUDE_DIR}/imgui/*.cpp
    ${VENDOR_INCLUDE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${VENDOR_INCLUDE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${VENDOR_INCLUDE_DIR}/imgui)
target_link_libraries(imgui PRIVATE glfw) # Ensure ImGui links against GLFW

# -------------------------
# Export include dirs and targets
# -------------------------
set(VENDOR_LIBRARIES glfw imgui mariadbcpp CACHE INTERNAL "")
set(VENDOR_INCLUDE_DIRS
    ${VENDOR_INCLUDE_DIR}/glfw/include
    ${VENDOR_INCLUDE_DIR}/mariadbc/include
    ${VENDOR_INCLUDE_DIR}/imgui
    CACHE INTERNAL ""
)
