cmake_minimum_required(VERSION 3.22)

project(plut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Since all dependencies can be linked to core, which is 
# linked to client's shared library, we just build everything as PIC
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_compile_options("-Wall")

set(PLUT_BUILD_TESTS ON)
set(PLUT_BUILD_EXAMPLES ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
	add_link_options(-fprofile-instr-generate -fcoverage-mapping)
endif()

# Dependencies
add_subdirectory(thirdparty/spdlog)
add_subdirectory(thirdparty/cxxopts)

# set(Boost_DEBUG ON)
find_package(Boost COMPONENTS container REQUIRED)

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Projects
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
