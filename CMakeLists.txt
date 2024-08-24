cmake_minimum_required(VERSION 3.22)

project(plut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("-Wall")

set(PLUT_BUILD_TESTS ON)
set(PLUT_BUILD_EXAMPLES ON)

add_subdirectory(core)
add_subdirectory(benchmark)
add_subdirectory(cli)
add_subdirectory(server)

if(${PLUT_BUILD_EXAMPLES})
	add_subdirectory(example)
endif()

add_custom_target(code-format
	COMMAND "./code-format.sh"
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
