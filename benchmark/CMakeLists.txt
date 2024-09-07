project(${CMAKE_PROJECT_NAME}_benchmark)

set(SOURCES src/BenchmarkLogger.cc src/Measurer.cc src/Runner.cc src/main.cc)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include/)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_core)
