group "vendor"

-- GLFW submodule path
local glfwPath = "glfw"
local glfwBuild = path.join(glfwPath, "build")

-- Make sure submodule exists and is updated
if not os.isdir(glfwPath) then
    print("GLFW submodule not found, cloning...")
    os.execute("git submodule update --init --recursive")
else
    print("Updating GLFW submodule...")
    os.execute("git submodule update --remote --merge")
end

-- Build GLFW with CMake if build dir doesn't exist
if not os.isdir(glfwBuild) then
    os.mkdir(glfwBuild)
end

os.chdir(glfwBuild)
-- Build all configurations with CMake
os.execute("cmake .. -DBUILD_SHARED_LIBS=OFF")
os.execute("cmake --build .")
os.chdir("../..")

-- Now other projects can link with GLFW by specifying include and lib paths
glfwIncludeDir = "vendor/glfw/include"
glfwLibDir = "vendor/glfw/build/src"

group ""
