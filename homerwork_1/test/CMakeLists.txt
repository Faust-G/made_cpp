cmake_minimum_required(VERSION 3.0.0)
project(test_weather)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES_C "*.cpp")

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES_C} ${SR})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}  GTest::gtest_main)

gtest_discover_tests(${PROJECT_NAME})