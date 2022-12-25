cmake_minimum_required(VERSION 3.22)
project(adventofcode)

set(CMAKE_CXX_STANDARD 14)



include_directories(2022)

#add_executable(adventofcode 2022/day05_p1.cpp)
#add_executable(adventofcode 2022/day06_p1_2.cpp)
#add_executable(adventofcode 2022/day07_p1_2.cpp)
#add_executable(adventofcode 2022/day08_p1_2.cpp)
#add_executable(adventofcode 2022/day09_p1_2.cpp)

#add_executable(adventofcode 2022/day10_p1.cpp)
#add_executable(adventofcode 2022/day10_p2.cpp)

#day 11
#add_executable(adventofcode 2022/day11_p1.cpp)

#FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
#add_executable(adventofcode 2022/day11_p2.cpp)
#TARGET_LINK_LIBRARIES( adventofcode LINK_PUBLIC ${Boost_LIBRARIES} )

# day 12
add_library(grid STATIC 2022/day12/grid.cpp)
add_executable(adventofcode 2022/day12/day12_p1_2.cpp)
target_link_libraries(adventofcode grid)