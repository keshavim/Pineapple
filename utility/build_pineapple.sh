#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="${SCRIPT_DIR}/.."
BUILD_DIR="${ROOT_DIR}/build"

# Allow generator selection: default Makefiles, or pass "ninja" or "vs" as arg
GENERATOR=${1:-make}

echo "=== Configuring CMake project with generator: $GENERATOR ==="
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

case "$GENERATOR" in
    ninja)
        cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug "$ROOT_DIR"
        ;;
    make)
        cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug "$ROOT_DIR"
        ;;
    *)
        echo "Unknown generator: $GENERATOR"
        echo "Usage: $0 [make|ninja]"
        exit 1
        ;;
esac

echo "=== Building ==="
cmake --build  . -j"$(nproc)"
echo "=== Project build complete ==="
