/**
 * @file Menu.cpp
 * @brief Implementation of Menu class used for interaction with user during the game
 * @author Matija Šeremet
 * @date 26.12.2023.
 */

#include "Menu.h"
#include "Sudoku9.h"
#include <iostream>
#include <fstream>
#include <sstream>


Menu::Menu() : choice(0), whoSolvesChoice(0) {}

void Menu::printOptions() {
    std::cout << "*------*" << std::endl;
    std::cout << "Welcome to our menu for playing Sudoku game!" << std::endl << std::endl;
    std::cout << "1. Load a sudoku puzzle from the file." << std::endl;
    std::cout << "2. Generate new sudoku puzzle and write it to the file 'mySudoku.txt'." << std::endl;
    std::cout << "3. Exit the application" << std::endl;

}

unsigned short Menu::chooseOption(unsigned short downLimit, unsigned short upLimit) {
    unsigned short number;
    while (true) {
        std::cout << ">> Enter a number: ";
        std::cin >> number;

        if (std::cin.fail()) { // char input
            std::cout << "Error: Invalid input. Please enter a number between " << downLimit << " and " << upLimit << "." << std::endl;
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            continue;
        }

        if (number <= upLimit && number >= downLimit) {
            break;
        } else {
            std::cout << "Error: You chose an invalid option." << std::endl;
        }
    }
    return number;
}

void Menu::whoSolves() {
    std::cout << "  1. Check my solution of sudoku from the file." << std::endl;
    std::cout << "  2. Let the computer solve sudoku puzzle." << std::endl;
    whoSolvesChoice = Menu::chooseOption(1, 2);
}

void Menu::menuLoop() {
    while (choice != 3) {
        printOptions();
        choice = Menu::chooseOption(1, 3);

        // generated puzzle and written in the file
        if (choice == 2) {
            playGame("mySudoku.txt", false);

        }
        else if (choice == 1){
            playGame("mySudoku.txt", true);
        }
    }
}

void Menu::playGame(char* fileName, bool userCreated) {
    try {

        Sudoku9 solvedSudoku;
        unsigned short usersGeneratedPlaces = 0;
        if (!userCreated) {
            solvedSudoku.generateSudokuPuzzle();
            writeSudokuInFile(fileName, solvedSudoku.getMatrix());

        } else if (solvedSudoku.isUnsolvedSudokuValid(fileName, usersGeneratedPlaces)) {
            unsigned short **matrix = loadSudokuFromFile(fileName);
            solvedSudoku.setMatrix(matrix);
            solvedSudoku.setGeneratedPlaces(81 - usersGeneratedPlaces);;
        }
        if (!solvedSudoku.solveSudoku())
            std::cout << "Error: Unable to solve the sudoku puzzle." << std::endl;
        whoSolves();

        // user plays the game
        if (whoSolvesChoice == 1) {
            unsigned short **matrix = loadSudokuFromFile(fileName);
            Sudoku9 usersSudoku(matrix);
            Sudoku9::gameNumber--;    // 2 puzzles are created, but only one is played
            usersSudoku.setGeneratedPlaces(solvedSudoku.getGeneratedPlaces());
            usersSudoku.printSudokuTable();
            usersSudoku.evaluateSudoku(solvedSudoku);

            writeSudokuInFile("solvedSudoku.txt", solvedSudoku.getMatrix());

            // computer solves sudoku
        } else if (whoSolvesChoice == 2) {
            solvedSudoku.printSudokuTable();
            solvedSudoku.evaluateSudoku(solvedSudoku);
        } else {
            std::cout << "Error: You chose invalid option." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

void Menu::writeSudokuInFile(char* fileName, unsigned short** matrix) {
    std::ofstream outputFile;
    outputFile.open(fileName);

    if (!outputFile.is_open()) {    // checking if the file is opened successfully
        std::cerr << "Error: Unable to open the file " << fileName << "."<< std::endl;
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            outputFile << matrix[i][j] << " ";
        }
        outputFile << std::endl;
    }
    outputFile.close();
}

unsigned short** Menu::loadSudokuFromFile(char *fileName) {
    std::ifstream inputFile(fileName);

    // check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file" << std::endl;
    }

    std::string line;
    auto** matrix= new unsigned short*[9];

    int i = 0;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        matrix[i] = new unsigned short[9]();

        for (int j = 0; j < 9; ++j) {
            unsigned short num;
            iss >> num;
            matrix[i][j] = num;
        }
        ++i;
    }
    inputFile.close();
    return matrix;
}

