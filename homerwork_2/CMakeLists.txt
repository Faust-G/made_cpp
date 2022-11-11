cmake_minimum_required(VERSION 3.14)
project(test_matrix)

execute_process (
    COMMAND bash -c "which g++"
    OUTPUT_VARIABLE compiler
)
string(REPLACE "\n" "" compiler "${compiler}")
message("COMPILER - ${compiler}")

set(CMAKE_CXX_COMPILER "${compiler}")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
 
file(GLOB SOURCES test.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(GTest REQUIRED)
 
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)