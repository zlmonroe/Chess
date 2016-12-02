cmake_minimum_required(VERSION 3.6)
project(Chess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/magics.h src/MoveGenerator.cpp src/MoveGenerator.h src/player.cpp src/player.h src/printBitboard.cpp src/printBitboard.h src/main.cpp src/ChessBoard.cpp src/ChessBoard.h src/ChessConstBitboards.h)
add_executable(Chess ${SOURCE_FILES})