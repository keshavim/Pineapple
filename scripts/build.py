import os
import subprocess
import sys
import platform
import argparse

def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="Run Premake5 with platform defaults or overrides.")
    parser.add_argument(
        "--vs2022", action="store_true",
        help="Force use of Visual Studio 2022"
    )
    parser.add_argument(
        "--gmake", action="store_true",
        help="Force use of GNU Make"
    )
    parser.add_argument(
        "--ninja", action="store_true",
        help="Force use of Ninja"
    )
    args = parser.parse_args()

    # Get the directory of this script
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Move one level up from script directory
    root_dir = os.path.abspath(os.path.join(script_dir, ".."))
    os.chdir(root_dir)

    # Path to premake5 executable
    premake_exe = os.path.join(root_dir, "vendor", "premake", "premake5")

    # Default action based on platform
    system = platform.system()
    if system == "Windows":
        default_action = "vs2022"
        premake_exe += ".exe"
    else:
        default_action = "gmake"

    # Override if user provided args
    if args.vs2022:
        action = "vs2022"
    elif args.gmake:
        action = "gmake"
    elif args.ninja:
        action = "ninja"
    else:
        action = default_action

    # Full command
    cmd = [premake_exe, action, "--file=build.lua"]

    try:
        subprocess.check_call(cmd)
    except subprocess.CalledProcessError as e:
        print(f"Premake failed with exit code {e.returncode}")
        sys.exit(e.returncode)

if __name__ == "__main__":
    main()
