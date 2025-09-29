import os
import sys
import subprocess
import platform

def main():
    # Get the directory of this script
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Move one level up
    root_dir = os.path.abspath(os.path.join(script_dir, ".."))
    os.chdir(root_dir)

    # Build/bin path
    bin_dir = os.path.join(root_dir, "build", "bin")
    if not os.path.isdir(bin_dir):
        print(f"Error: {bin_dir} does not exist.")
        sys.exit(1)

    # Expect exactly one folder inside bin
    subfolders = [f for f in os.listdir(bin_dir) if os.path.isdir(os.path.join(bin_dir, f))]
    if not subfolders:
        print("Error: No subfolders found in build/bin/")
        sys.exit(1)
    if len(subfolders) > 1:
        print("Warning: Multiple subfolders found in build/bin/, using the first one.")

    target_dir = os.path.join(bin_dir, subfolders[0])

    # Detect system
    system = platform.system()
    exe_ext = ".exe" if system == "Windows" else ""

    # Find the executable (skip libs)
    exe_path = None
    for f in os.listdir(target_dir):
        full_path = os.path.join(target_dir, f)
        if os.path.isfile(full_path):
            if system == "Windows":
                if f.lower().endswith(".exe"):
                    exe_path = full_path
                    break
            else:
                if os.access(full_path, os.X_OK) and not f.endswith((".so", ".dylib")):
                    exe_path = full_path
                    break

    if not exe_path:
        print("Error: No executable found in target folder.")
        sys.exit(1)

    # Run the executable
    print(f"Running: {exe_path}")
    try:
        subprocess.check_call([exe_path])
    except subprocess.CalledProcessError as e:
        print(f"Executable exited with code {e.returncode}")
        sys.exit(e.returncode)

if __name__ == "__main__":
    main()
