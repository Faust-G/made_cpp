cmake_minimum_required(VERSION 3.0.0)
project(weather_lib)

execute_process (
    COMMAND bash -c "which g++"
    OUTPUT_VARIABLE compiler
)
string(REPLACE "\n" "" compiler "${compiler}")
message("COMPILER - ${compiler}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/made_cpp/homerwork_4/boost_1_80_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/made_cpp/homerwork_4/boost_1_80_0/libs")

find_package(Boost)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(weather help_func.cpp)


target_include_directories(weather PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(weather  ${Boost_LIBRARIES}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        pthread rt)
file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE rt pthread boost_filesystem)

set(WEATHER_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(WEATHER_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)