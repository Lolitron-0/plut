#!/bin/bash

set -e

cmake -S . \
			-B build \
			-G Ninja \
			-DCMAKE_CXX_COMPILER=clang++-18 \
			-DCMAKE_C_COMPILER=clang-18 \
			-DCMAKE_BUILD_TYPE=Debug \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=1 
cmake --build build --parallel $(nproc)

cp -f build/compile_commands.json .

./build/$1/plut_$1
			
