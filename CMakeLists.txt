cmake_minimum_required(VERSION 3.10)
project(AdventOfCode2025)

add_library(helper_functions helpers/helpers.cpp)

target_include_directories(helper_functions PUBLIC helpers)

# add_executable(day5_program 2025/day5/day5.cpp)
# target_link_libraries(day5_program PRIVATE helper_functions)

add_executable(day5_program 2025/day5/day5p2.cpp)
target_link_libraries(day5_program PRIVATE helper_functions)
