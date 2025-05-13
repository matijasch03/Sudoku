cmake_minimum_required(VERSION 3.27)
project(Sudoku)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sudoku main.cpp
        Sudoku9.h
        Sudoku9.cpp
        Menu.cpp
        Menu.h
        Tests/SudokuTest.cpp
        Tests/SudokuTest.h
        Tests/main.cpp)
