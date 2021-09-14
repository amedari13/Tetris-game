cmake_minimum_required(VERSION 3.15)

# задаем название проекта
project(Tetris VERSION 1.0)

# указать стандарт C ++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# добавляем исполняемые файлы
add_executable(Tetris Tetris.cpp Field.cpp Figure.cpp Game.cpp) 

SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")