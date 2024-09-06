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

# $1 - test dir 
# $2 - test name 
run_test() {
	pushd $1 > /dev/null
	LLVM_PROFILE_FILE="$2.profraw" ./$2
	llvm-profdata-18 merge -sparse $2.profraw -o $2.profdata
	llvm-cov-18 export ./$2 --instr-profile=$2.profdata --format=lcov > coverage.info
	lcov --remove coverage.info -o coverage_filtered.info \
		'*spdlog*' \
		'*build/*' > /dev/null
	popd > /dev/null
	genhtml $1/coverage_filtered.info --branch-coverage --output-directory ./build/coverage_report/$2 > /dev/null
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
export LLVM_PROFILE_FILE="./build/default.profraw"

if [ $1 == "cli" ]; then
	./build/cli/plut_cli $example_to_launch
elif [ $1 == "benchmark" ]; then
	./build/benchmark/plut_benchmark $example_to_launch
elif [ $1 == "test" ]; then
	if [ -z $2 ]; then
		usage_and_exit
	fi

	if [ $2 == "core" ]; then
		test_dir=./build/core/test
		test_name=plut_core_tests
	else
		usage_and_exit
	fi

	run_test $test_dir $test_name
else
	usage_and_exit
fi
			
