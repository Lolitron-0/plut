set(PARENT_PROJECT_NAME ${PROJECT_NAME})
project(${PARENT_PROJECT_NAME}_tests)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_compile_definitions(PLUT_NO_LOGS=1)

add_executable(${PROJECT_NAME} core_gtest.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PARENT_PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main GTest::gtest)

# target_compile_options(${PROJECT_NAME} PRIVATE "-fsanitize=address")
# target_link_options(${PROJECT_NAME} PRIVATE "-fsanitize=address")

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
