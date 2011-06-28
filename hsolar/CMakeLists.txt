cmake_minimum_required (VERSION 2.6)
project (solar)
set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(hsolar main)

include_directories("${PROJECT_BINARY_DIR}")
add_subdirectory(includes)