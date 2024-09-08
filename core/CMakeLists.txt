project(${CMAKE_PROJECT_NAME}_core)

set(SOURCES
    src/SlotBase.cc
    src/Logger.cc
    src/Symbol.cc
    src/Reel.cc
    src/Board.cc
    src/PassPresets.cc
    src/WinLine.cc
    src/Cell.cc
    src/SymbolManager.cc
    src/SlotLoader.cc)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

# Coverage
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(${PROJECT_NAME} PUBLIC -fprofile-instr-generate
                                                -fcoverage-mapping)
  target_link_options(${PROJECT_NAME} PUBLIC -fprofile-instr-generate
                      -fcoverage-mapping)
endif()

# Dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC cxxopts)


if(PLUT_BUILD_TESTS)
  add_subdirectory(test)
endif()
