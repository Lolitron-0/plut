project(${CMAKE_PROJECT_NAME}_core)
# we will link core to client's .so
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

set(SOURCES src/SlotBase.cc src/Logger.cc src/Symbol.cc src/Reel.cc
            src/Board.cc src/PassPresets.cc)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

# Coverage
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(${PROJECT_NAME} PUBLIC -fprofile-instr-generate
                                                -fcoverage-mapping)
  target_link_options(${PROJECT_NAME} PUBLIC -fprofile-instr-generate
                      -fcoverage-mapping)
endif()

add_subdirectory(thirdparty/spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

if(PLUT_BUILD_TESTS)
  add_subdirectory(test)
endif()
