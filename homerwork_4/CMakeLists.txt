cmake_minimum_required(VERSION 3.0.0)
project(sport)

execute_process (
    COMMAND bash -c "which g++"
    OUTPUT_VARIABLE compiler
)
string(REPLACE "\n" "" compiler "${compiler}")
message("COMPILER - ${compiler}")

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_subdirectory(lib)

message("WEATHER_LIB_INCLUDE_DIRS= ${WEATHER_LIB_INCLUDE_DIRS}")
message("WEATHER_LIB_LIBRARIES = ${WEATHER_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${WEATHER_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${WEATHER_LIB_LIBRARIES})
