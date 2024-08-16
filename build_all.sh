#!/bin/bash

set -e

cmake -S . \
			-B build \
			-G Ninja \
			-DCMAKE_CPP_COMPILER=clang++-18 \
			-DCMAKE_C_COMPILER=clang-18 \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=1 
cmake --build build --parallel $(nproc)

cp build/compile_commands.json .
			
