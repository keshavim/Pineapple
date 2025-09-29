#!/bin/bash

cd "$(dirname "$0")" || exit

pushd ..
premake5 export-compile-commands --file=build.lua
mv build/compile_commands/debug.json compile_commands.json


popd || exit
