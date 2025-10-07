#!/bin/bash

set -e

# Default configuration
CONFIG=${1:-Debug}

# Ensure we're in the parent directory of the script (where CMakeLists.txt is)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR/.." || exit 1

# Create build directory if it doesn't exist
mkdir -p build

# Check if Ninja is available
if command -v ninja >/dev/null 2>&1; then
    GENERATOR="Ninja"
    echo "Using Ninja as the build system generator"
else
    GENERATOR="Unix Makefiles"
    echo "Ninja not found, falling back to Make"
fi

# Configure with CMake, ensuring compile_commands.json is generated
cmake -S . -B build -G "$GENERATOR" -DCMAKE_BUILD_TYPE="$CONFIG" -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
if [ $? -ne 0 ]; then
    echo "CMake configuration failed"
    exit 1
fi

# Build the project
cmake --build build --config "$CONFIG"
if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1
fi

# Ensure compile_commands.json is in build/
if [ -f "compile_commands.json" ]; then
    mv compile_commands.json build/
fi

echo "Build completed successfully in build/bin/$CONFIG"
