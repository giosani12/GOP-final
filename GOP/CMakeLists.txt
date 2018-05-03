cmake_minimum_required(VERSION 3.6)
project(GOP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Source.cpp GAME.cpp GAME.h PLAYER.cpp PLAYER.h TABLE.cpp TABLE.h CARD.cpp CARD.h)

add_executable(GOP ${SOURCE_FILES})