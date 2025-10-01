
-------------------------
-- GLFW (needs CMake)
-------------------------
if not os.isdir("glfw/build") then
    os.mkdir("glfw/build")
    os.chdir("glfw/build")
    os.execute("cmake .. -DBUILD_SHARED_LIBS=OFF")
    os.execute("cmake --build .")
    os.chdir("../..")
end
