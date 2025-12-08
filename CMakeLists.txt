cmake_minimum_required(VERSION 3.10)
project(AdventOfCode2025)

add_library(helper_functions helpers/helpers.cpp)

target_include_directories(helper_functions PUBLIC helpers)

# add_executable(day1_program 2025/day1/day1.cpp)
# target_link_libraries(day1_program PRIVATE helper_functions)

# add_executable(day2_program 2025/day2/day2.cpp)
# target_link_libraries(day2_program PRIVATE helper_functions)

# add_executable(day2_program 2025/day2/day2p2.cpp)
# target_link_libraries(day2_program PRIVATE helper_functions)

# add_executable(day3_program 2025/day3/day3.cpp)
# target_link_libraries(day3_program PRIVATE helper_functions)

# add_executable(day3_program 2025/day3/day3p2.cpp)
# target_link_libraries(day3_program PRIVATE helper_functions)

# add_executable(day4_program 2025/day4/day4.cpp)
# target_link_libraries(day4_program PRIVATE helper_functions)

add_executable(day4_program 2025/day4/day4p2.cpp)
target_link_libraries(day4_program PRIVATE helper_functions)
