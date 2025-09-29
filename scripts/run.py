import os
import subprocess
import sys

def main():
    # Change directory to script location
    script_dir = os.path.dirname(os.path.abspath(__file__))
    os.chdir(script_dir)

    # Move one level up
    os.chdir('..')

    # Run premake5 ninja
    ret = subprocess.run(['premake5', 'ninja'])
    if ret.returncode != 0:
        print("premake5 failed")
        sys.exit(ret.returncode)

    # Run ninja build
    ret = subprocess.run(['ninja', '-C', 'build'])
    if ret.returncode == 0:
        print("build successful")

        output_dir = os.path.join('build', 'bin')
        exe_path = None

        # Find an executable file named Sandbox exactly inside output_dir
        for root, dirs, files in os.walk(output_dir):
            for f in files:
                full_path = os.path.join(root, f)
                if os.path.basename(full_path) == 'Sandbox' and os.access(full_path, os.X_OK):
                    exe_path = full_path
                    break
            if exe_path:
                break

        if exe_path:
            subprocess.run([exe_path])
        else:
            print("exe not found")
    else:
        print("build unsuccessful")

if __name__ == "__main__":
    main()
