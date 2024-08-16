project(${CMAKE_PROJECT_NAME}_core)

set(SOURCES 
	src/test.cc
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

add_subdirectory(thirdparty/spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

