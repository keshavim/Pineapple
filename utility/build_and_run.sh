#!/usr/bin/env bash
set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR/" || exit 1

export CC=gcc
export CXX=g++
./build_pineapple.sh
./../build/bin/Debug/Sandbox
