


outputdir = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
outputdir_obj = "%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"



-------------------------
-- GLFW (needs CMake)
-------------------------
if not os.isdir("vendor/glfw/build") then
    os.mkdir("vendor/glfw/build")
    os.chdir("vendor/glfw/build")
    os.execute("cmake .. -DBUILD_SHARED_LIBS=OFF")
    os.execute("cmake --build .")
    os.chdir("../..")
end


external_files = {
    "../vendor/imgui/imgui.cpp",
    "../vendor/imgui/imgui_draw.cpp",
    "../vendor/imgui/imgui_tables.cpp",
    "../vendor/imgui/imgui_widgets.cpp",
    "../vendor/imgui/imgui_demo.cpp",

    "../vendor/imgui/backends/imgui_impl_glfw.cpp",
    "../vendor/imgui/backends/imgui_impl_glfw.h",
    "../vendor/imgui/backends/imgui_impl_opengl3.cpp",
    "../vendor/imgui/backends/imgui_impl_opengl3.h",

    "../vendor/nanodbc/nanodbc/nanodbc.h",
    "../vendor/nanodbc/nanodbc/nanodbc.cpp",
}
