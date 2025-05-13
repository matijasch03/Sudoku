/**
 * @file SudokuTest.h
 * @brief Declaration of SudokuTest class for testing functions of Sudoku9 class
 * @author Matija Šeremet
 * @date 27.12.2023.
 */

#ifndef SUDOKU_SUDOKUTEST_H
#define SUDOKU_SUDOKUTEST_H


class SudokuTest {
public:
    bool testLoadingSudoku();
    bool testInvalidLoadingSudoku();
    bool testCopyConstructor();

    bool testRangeSudoku();
    bool testSolvedSudokuValidity();
    bool testWritingInFile();
};


#endif //SUDOKU_SUDOKUTEST_H
