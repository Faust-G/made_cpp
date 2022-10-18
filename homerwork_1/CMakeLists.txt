cmake_minimum_required(VERSION 3.0.0)
project(weather VERSION 0.1.0)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
file(GLOB SOURCES "**/*.h" "*.c" "**/*.c" )
file(GLOB SR "**/*.h" "**/*.c" )
file(GLOB INCLUDE_DIRS weather)

add_executable(${PROJECT_NAME} ${SOURCES})

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})


message("this is SOURCES = ${SOURCES}")
message("this is INCLUDE_DIRS = ${INCLUDE_DIRS}")

enable_testing()
add_subdirectory(test)