#!/bin/bash

# Go to the script folder
cd "$(dirname "$0")" || exit

# Go to project root
pushd .. || exit

# Set clang as compiler
export CC=clang
export CXX=clang++

# Temporary build folder
TEMP_BUILD="temp_build"

mkdir -p "$TEMP_BUILD"
cd "$TEMP_BUILD" || exit

# Generate compile_commands.json with CMake + Ninja
cmake -G Ninja ..

# Move the JSON to project root
mv compile_commands.json ../compile_commands.json

# Go back to project root
popd || exit

rm -rf "$TEMP_BUILD"


echo "compile_commands.json generated at $(pwd)/compile_commands.json"
