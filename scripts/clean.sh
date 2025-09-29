#!/bin/bash

cd "$(dirname "$0")" || exit

pushd ..
rm -rf build
popd || exit
