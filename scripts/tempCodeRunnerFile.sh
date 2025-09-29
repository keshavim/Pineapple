#!/bin/bash

cd "$(dirname "$0")" || exit

python3 build.py --ninja

pushd ..
ninja -C build Debug
popd || exit

python3 run.py
