cmake_minimum_required(VERSION 3.6)
project(Chess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES MoveGenerator.cpp MoveGenerator.h magics.h MagicMoves.cpp queenmoves.cpp)
add_executable(Chess ${SOURCE_FILES})