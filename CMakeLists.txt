cmake_minimum_required(VERSION 3.10)
project(AdventOfCode2025)

add_library(helper_functions helpers/helpers.cpp)

target_include_directories(helper_functions PUBLIC helpers)

# add_executable(day5_program 2025/day5/day5.cpp)
# target_link_libraries(day5_program PRIVATE helper_functions)

# add_executable(day5_program 2025/day5/day5p2.cpp)
# target_link_libraries(day5_program PRIVATE helper_functions)

# add_executable(day6_program 2025/day6/day6.cpp)
# target_link_libraries(day6_program PRIVATE helper_functions)

# add_executable(day6_program 2025/day6/day6p2.cpp)
# target_link_libraries(day6_program PRIVATE helper_functions)

add_executable(day7_program 2025/day7/day7.cpp)
target_link_libraries(day7_program PRIVATE helper_functions)
