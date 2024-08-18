project(${CMAKE_PROJECT_NAME}_core)

set(SOURCES 
	src/SlotBase.cc
	src/Logger.cc
	src/Symbol.cc
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

add_subdirectory(thirdparty/spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

if(PLUT_BUILD_TESTS)
	add_subdirectory(test)
endif()


