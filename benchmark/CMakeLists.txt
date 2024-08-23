project(${CMAKE_PROJECT_NAME}_benchmark)

set(SOURCES src/main.cc)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include/)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_core)
