#!/bin/bash

mkdir -p build
cd build
cmake ..
# cmake -DCMAKE_CXX_FLAGS="-H" ..
cmake --build . #--verbose