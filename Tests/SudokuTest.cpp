/**
 * @file SudokuTest.h
 * @brief Implementation of SudokuTest class for testing functions of Sudoku9 class
 * @author Matija Šeremet
 * @date 27.12.2023.
 */

#include <fstream>
#include <iostream>
#include "SudokuTest.h"
#include "../Sudoku9.h"
#include "../Menu.h"


bool SudokuTest::testLoadingSudoku() {
    unsigned short** matrix = new unsigned short * [9];
    for (int i = 0; i < 9; ++i) {
        matrix[i] = new unsigned short [9];
        for (int j = 0; j < 9; ++j) {
            matrix[i][j] = j;
        }
    }
    Sudoku9 sudoku9(matrix);
    return sudoku9.getGeneratedPlaces() == 72;
}

bool SudokuTest::testInvalidLoadingSudoku() {
    unsigned short** matrix = new unsigned short * [9];
    for (int i = 0; i < 9; ++i) {
        matrix[i] = new unsigned short [8];
        for (int j = 0; j < 8; ++j) {
            matrix[i][j] = j;
        }
    }
    Sudoku9 sudoku9(matrix);
    return sudoku9.getGeneratedPlaces() == 63;
}

bool SudokuTest::testCopyConstructor() {
    Sudoku9 sudoku9;
    Sudoku9 sudCopy(sudoku9);
    unsigned short** matrix = sudoku9.getMatrix();
    unsigned short** copyMatrix = sudCopy.getMatrix();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (matrix[i][j] != copyMatrix[i][j]) {
                return false;
            }
        }
    }
    return sudoku9.getGeneratedPlaces() == sudCopy.getGeneratedPlaces() && sudoku9.getRightPlaces() == sudCopy.getRightPlaces();
}

bool SudokuTest::testRangeSudoku() {
    Sudoku9 sudoku9;
    sudoku9.generateSudokuPuzzle();
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {

            if (sudoku9.getMatrix()[i][j] < 0 || sudoku9.getMatrix()[i][j] > 9) {
                return false;
            }
        }
    }
    return sudoku9.getGeneratedPlaces() <= 54;
}

bool SudokuTest::testSolvedSudokuValidity() {
    Sudoku9 sudoku9;
    sudoku9.generateSudokuPuzzle();
    sudoku9.solveSudoku();
    return sudoku9.isSudokuValid();
}

bool SudokuTest::testWritingInFile() {
    Sudoku9 s;
    Menu menu;
    s = menu.loadSudokuFromFile("infile.txt");
    menu.writeSudokuInFile("outfile.txt", s.getMatrix());
    std::ifstream inputFile("outfile.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
    }

    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    return fileContent == "0 7 6 0 0 3 0 0 8\n"
                          "0 0 8 0 0 0 3 7 6\n"
                          "0 4 0 7 8 0 2 5 1\n"
                          "5 0 2 0 0 1 0 6 3\n"
                          "4 1 7 0 6 8 0 0 9\n"
                          "6 0 3 2 5 7 8 1 4\n"
                          "0 2 4 0 1 5 6 3 7\n"
                          "7 6 0 0 0 2 9 4 5\n"
                          "0 3 5 6 0 4 1 8 2\n";

}
