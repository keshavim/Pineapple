
# -------------------------
# Paths
# -------------------------
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
file(GLOB IMGUI_SRC CONFIGURE_DEPENDS
    ${VENDOR_DIR}/imgui/*.cpp
    ${VENDOR_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${VENDOR_DIR}/imgui/backends/imgui_impl_opengl3.cpp

    ${VENDOR_DIR}/imgui/*.h
    ${VENDOR_DIR}/imgui/backends/imgui_impl_glfw.h
    ${VENDOR_DIR}/imgui/backends/imgui_impl_opengl3.h
)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${VENDOR_DIR}/imgui)
target_link_libraries(imgui PRIVATE glfw)


# -------------------------
# GLAD
# -------------------------
file(GLOB GLAD_SRC CONFIGURE_DEPENDS
    ${VENDOR_DIR}/glad/src/glad.c
    ${VENDOR_DIR}/glad/include/glad/glad.h
    ${VENDOR_DIR}/glad/include/KHR/khrplatform.h

)

add_library(glad STATIC ${GLAD_SRC})
target_include_directories(glad PUBLIC ${VENDOR_DIR}/glad/include)

# -------------------------
# Export include dirs and targets
# -------------------------
set(VENDOR_LIBRARIES glfw glad imgui mariadbcpp CACHE INTERNAL "")
set(VENDOR_INCLUDE_DIRS
    ${VENDOR_DIR}/glfw/include
    ${VENDOR_DIR}/mariadbc/include
    ${VENDOR_DIR}/imgui
    ${VENDOR_DIR}/glad/include
    CACHE INTERNAL ""
)
