/**
 * @file SudokuTest.cpp
 * @brief Implementation of SudokuTest class for testing functions of Sudoku9 class
 * @author Matija Šeremet
 * @date 27.12.2023.
 */

#include <iostream>
#include <random>
#include <cstring>
#include "Sudoku9.h"

int Sudoku9::gameNumber = 0;

Sudoku9::Sudoku9() : generatedPlaces(0), rightPlaces(0) {
    matrix = new unsigned short*[9];
    for (int i = 0; i < 9; ++i) {
        // set all values to 0
        matrix[i] = new unsigned short[9]();
    }
    gameNumber++;
}

Sudoku9::Sudoku9(unsigned short** iMatrix) : rightPlaces(0), generatedPlaces(81) {
    matrix = iMatrix;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (matrix[i][j] == 0)
                generatedPlaces--;
        }
    }
    gameNumber++;
}

Sudoku9::Sudoku9(const Sudoku9 &other) : generatedPlaces(other.generatedPlaces), rightPlaces(other.rightPlaces) {
    matrix = new unsigned short*[9];
    for (int i = 0; i < 9; ++i) {
        matrix[i] = new unsigned short[9]();

        for (int j = 0; j < 9; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
    gameNumber++;
}

Sudoku9::~Sudoku9() {
    for (int i = 0; i < 9; ++i) {
        delete[] matrix[i];     // deleting lines
    }
    delete[] matrix;    // deleting an array of pointers
}

unsigned short Sudoku9::getGeneratedPlaces() {
    return generatedPlaces;
}

unsigned short Sudoku9::getRightPlaces() {
    return rightPlaces;
}

void Sudoku9::setGeneratedPlaces(unsigned short v) {
    generatedPlaces = v;
}

void Sudoku9::setRightPlaces(unsigned short v) {
    rightPlaces = v;
}

void Sudoku9::printSudokuTable() {
    std::cout << "-------------------" << std::endl;
    for (int i = 0; i < 9; ++i) {
        std::cout << "|";   // separator between each number

        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 2)
                std::cout << matrix[i][j] << "|";
            else
                std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;     // the end of one row
        // after each 3 rows print lines that separate blocks of 3 little squares 3x3
        if (i % 3 == 2) {
            std::cout << "-------------------" << std::endl;
        }
    }
}

bool Sudoku9::unusedInBox(int row, int col, unsigned short num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[row + i][col + j] == num) {
                return false;
            }
        }
    }
    return true;
}

void Sudoku9::generateSudokuPuzzle() {
    // fill the diagonal of 3x3 matrices
    for (int i = 0; i < 9; i += 3)
    {
        unsigned short num;
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                do {
                    // creating random numbers 1-9 which will be added in each of 3 squares 3x3 on diagonals
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dist(1, 9);
                    num = dist(gen);
                    // the only condition is that there isn't any repeating of numbers in each box
                } while (!unusedInBox(i, i, num));
                matrix[i + j][i + k] = num;
            }
        }
    }

    // fill remaining blocks
    fillRemaining(0, 3);

    // randomly remove some digits to make game
    removeDigits();
}

bool Sudoku9::unusedInRow(int i, int num) {
    for (int j = 0; j < 9; j++) {
        if (matrix[i][j] == num) {
            return false;
        }
    }
    return true;
}

bool Sudoku9::unusedInCol(int j, int num) {
    for (int i = 0; i < 9; i++) {
        if (matrix[i][j] == num) {
            return false;
        }
    }
    return true;
}

bool Sudoku9::checkIfSafe(int i, int j, int num) {
    return (unusedInRow(i, num) && unusedInCol(j, num)
            && unusedInBox(i - i % 3, j - j % 3, num));
}

bool Sudoku9::fillRemaining(int i, int j) {
    // matrix is at the end of the row
    if (j >= 9 && i < 8) {
        i++;
        j = 0;
    }

    // it's the end of sudoku 9x9
    if (i >= 9 && j >= 9) {
        return true;
    }

    // blocks on the main diagonal are filled, so it's necessary to skip them
    // check if we are in the first block
    if (i < 3) {
        if (j < 3) {
            j = 3;
        }
    }

    // check if we're in the middle block
    else if (i < 6) {
        if (j == (int)(i / 3) * 3) {
            j += 3;
        }
    }

    else {
        // check if we're in the last block
        if (j == 6) {
            i ++;
            j = 0;
            // it could be the end of the table, but it if there are more rows, just set j to 0
            if (i >= 9) {
                return true;
            }
        }
    }
    for (int num = 1; num <= 9; ++num) {
        if (checkIfSafe(i, j, num)) {
            matrix[i][j] = num;
            if (fillRemaining(i, j + 1)) {
                return true;
            }
            matrix[i][j] = 0;  // reset the value if it's not returned true
        }
    }
    return false;
}

void Sudoku9::removeDigits() {
    // random generator for number of removed cells
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(28, 48);
    int count = dist(gen);
    generatedPlaces = 81 - count;
    rightPlaces = count;

    while (count != 0) {
        // random generator for cellId that says which cells will be removed
        std::uniform_int_distribution<> dist(0, 80);
        int cellId = dist(gen);

        int i = (cellId / 9);
        int j = cellId % 9;
        if (j != 0) {
            j--;
        }
        if (matrix[i][j] != 0) {
            count--;
            matrix[i][j] = 0;
        }
    }
}

bool Sudoku9::findUnassignedLocation(int& row, int& col)
{
    for (row = 0; row < 9; ++row)
        for (col = 0; col < 9; ++col)
            if (matrix[row][col] == 0)
                return true;
    return false;
}

bool Sudoku9::solveSudoku() {
    int row, col;
    rightPlaces = 81 - generatedPlaces;

    // if there is no unassigned location, it's the end
    if (!findUnassignedLocation(row, col))
        return true;

    for (int num = 1; num <= 9; ++num)
    {
        // check if it looks promising
        if (checkIfSafe(row, col, num))
        {
            // make tentative assignment       
            matrix[row][col] = num;
            if (solveSudoku())
                return true;

            matrix[row][col] = 0;   // this value has to be switched if it can
        }
    }
    // this triggers backtracking
    return false;
}

bool Sudoku9::isInRange() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {

            if (matrix[i][j] <= 0 || matrix[i][j] > 9) {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku9::isSudokuValid() {
    if (!isInRange()) {
        return false;
    }

    // stores unique value from 1 to 10
    bool unique[10];
    // checking rows
    for (int i = 0; i < 9; ++i) {

        // initialize unique[] array to false
        memset(unique, false,sizeof(unique));
        for (int j = 0; j < 9; ++j) {
            int Z = matrix[i][j];
            if (unique[Z]) {
                return false;
            }
            unique[Z] = true;
        }
    }

    // checking columns
    for (int i = 0; i < 9; ++i) {

        memset(unique, false,sizeof(unique));
        for (int j = 0; j < 9; ++j) {
            int Z = matrix[j][i];
            if (unique[Z]) {
                return false;
            }
            unique[Z] = true;
        }
    }

    // checking blocks 3x3
    for (int i = 0; i < 7; i += 3) {
        // j stores the first column of each 3 * 3 block
        for (int j = 0; j < 7; j += 3) {
            memset(unique, false, sizeof(unique));
            for (int k = 0; k < 3; ++k) {

                for (int l = 0; l < 3; ++l) {
                    int X = i + k;  // current row
                    int Y = j + l;  //current col
                    int Z = matrix[X][Y];
                    if (unique[Z]) {
                        return false;
                    }
                    unique[Z] = true;
                }
            }
        }
    }
    // if all conditions satisfied
    return true;
}

void Sudoku9::evaluateSudoku(Sudoku9 &solved) {
    if (isSudokuValid()) {
        std::cout << "Number of right cells: " << rightPlaces << "/" << rightPlaces << std::endl;
        std::cout << "Number of mistakes: 0" << std::endl;
    }

    else if (isInRange()){
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (matrix[i][j] == solved.getMatrix()[i][j]) {
                    rightPlaces++;
                }
            }
        }
        rightPlaces -= generatedPlaces;
        short mistakes = solved.getRightPlaces() - rightPlaces;
        if (mistakes < 0){
            std::cout << "Error: It's forbidden to change fields different from 0." << std::endl;
        }
        else {
            std::cout << "Number of right cells: " << rightPlaces << "/" << solved.getRightPlaces() << std::endl;
            std::cout << "Number of mistakes: " << mistakes << std::endl;
        }
    }
    else {
        std::cout << "Error: There are some other symbols or numbers out of interval 1-9." << std::endl;
    }
    std::cout << "Game number: " << gameNumber << std::endl;

}
