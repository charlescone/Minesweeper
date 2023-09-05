cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(minesweeper main.cpp welcome.cpp welcome.h board.h board.cpp board.cpp tile.h tile.cpp texture.h texture.cpp buttons.cpp buttons.h leaderboard.cpp leaderboard.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio)