
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

-------------------------
-- nanodbc
-------------------------
local nanodbc_dir = "nanodbc"
local build_dir = nanodbc_dir .. "/build"


if not os.isdir(build_dir) then
    os.mkdir(build_dir)
    os.chdir(build_dir)

    -- Build only the nanodbc library, no tests, no examples
    os.execute(
        "cmake .. " ..
        "-DCMAKE_BUILD_TYPE=Release " ..
        "-DBUILD_TESTS=OFF " ..
        "-DBUILD_EXAMPLES=OFF " ..
        "-DBUILD_SHARED_LIBS=OFF " ..
        "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=" .. build_dir .. "/lib"
    )

    os.execute("cmake --build .")
    os.chdir("../..")
end
