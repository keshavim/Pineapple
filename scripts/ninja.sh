#!/bin/bash

cd "$(dirname "$0")"

python3 build.py --ninja

pushd ..
ninja -C build
popd

python3 run.py
