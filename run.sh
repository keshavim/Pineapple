#!/bin/bash

cd "$(dirname "$0")"

premake5 ninja


ninja -C build



if [ $? -eq 0 ]; then
    echo "build sucessful"

    OUTPUT_DIR="build/bin"
    EXE=$(find "$OUTPUT_DIR" -type f -executable | grep -E "Sandbox$" | head -n 1)
    
    if [ -n "$EXE" ]; then
        ./$EXE
    else 
        echo "exe not found"
    fi
else
    echo build unsucesful
fi