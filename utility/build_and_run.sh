#!/usr/bin/env bash
set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit 1

export CC=gcc
export CXX=g++

./build_pineapple.sh

# Build absolute path to Sandbox
APP_PATH="$(realpath "$SCRIPT_DIR/../build/bin/Debug/Sandbox")"

# echo "Running with NVIDIA GPU: $APP_PATH"
__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia "$APP_PATH"
