cmake_minimum_required(VERSION 3.30)
project(chessgamecpp)

set(CMAKE_CXX_STANDARD 20)

# Find Google Test package
find_package(GTest REQUIRED)

# Add the executable target first
add_executable(chessgamecpp test_board.cpp
        Board.cpp
        include/Board.h)

# Link Google Test and pthread libraries to the executable
target_link_libraries(chessgamecpp ${GTEST_LIBRARIES} pthread)

# Include directories for Google Test
include_directories(${GTEST_INCLUDE_DIRS})
