cmake_minimum_required(VERSION 3.22)

project(plut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options("-Wall")

set(PLUT_BUILD_TESTS ON)

add_subdirectory(core)
add_subdirectory(benchmark)
add_subdirectory(cli)
add_subdirectory(server)

