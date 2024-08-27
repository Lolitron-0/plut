#!/bin/bash

set -e

HI='\033[0;33m'
NC='\033[0m'

usage_and_exit() {
	echo "Usage:"
	echo -e " ./dev.sh ${HI}<command>${NC} [options...]"
	echo ""
	echo "Possible commands:"
	echo -e " ${HI}help${NC}\t\t\t\t show this message"
	echo -e " ${HI}build${NC}\t\t\t\t build all"
	echo -e " ${HI}cli${NC}\t\t\t\t run cli demo"
	echo -e " ${HI}benchmark${NC}\t\t\t run benchmark"
	echo -e " ${HI}test <core/cli/benchmark>${NC}\t run tests on module"
	echo -e " ${HI}format${NC}\t\t\t\t format code"

	exit 0
}

build() {
cmake -S . \
			-B build \
			-G Ninja \
			-DCMAKE_CXX_COMPILER=clang++-18 \
			-DCMAKE_C_COMPILER=clang-18 \
			-DCMAKE_BUILD_TYPE=Debug \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=1 
cmake --build build --parallel $(nproc)

cp -f build/compile_commands.json .
}


if [ $1 == "help" ]; then
	usage_and_exit
elif [ $1 == "build" ]; then
	build
	exit 0
elif [ $1 == "format" ]; then
	./code-format.sh
	exit 0
fi

if [ -z $1 ]; then
	usage_and_exit
fi

build

example_to_launch="./build/example/libplut_example.so"

if [ $1 == "cli" ]; then
	./build/cli/plut_cli $example_to_launch
elif [ $1 == "benchmark" ]; then
	./build/benchmark/plut_benchmark $example_to_launch
elif [ $1 == "test" ]; then
	if [ -z $2 ]; then
		usage_and_exit
	fi

	if [ $2 == "core" ]; then
		./build/core/test/plut_core_tests
	else
		usage_and_exit
	fi
else
	usage_and_exit
fi
			
