/**
 * @file Menu.h
 * @brief Declaration of Menu class used for interaction with user during the game
 * @author Matija Šeremet
 * @date 26.12.2023.
 */

#ifndef SUDOKU_MENU_H
#define SUDOKU_MENU_H


#include "Sudoku9.h"

class Menu {
private:
    // the numbers that user is going to choose in menu
    unsigned short choice;
    unsigned short whoSolvesChoice;
public:
    /**
     * @brief Menu constructor without any parameters, only assign choice to 0
     */
     Menu();

     /**
      * @brief Print numerated options of menu on console
      */
      static void printOptions();

      /**
       * @brief The user should write a number from the menu
       * @param downLimit The lowest number that can be chosen
       * @param upLimit The highest number that can be chosen
       * @return The number that user chose
       */
      static unsigned short chooseOption(unsigned short downLimit, unsigned short upLimit);

      /**
      * @brief Show menubar to user until he exits (pressing 3)
      */
      void menuLoop();

      /**
       * @brief Ask user if he wants to computer solves sudoku from file or he
       */
       void whoSolves();

       /**
        * @brief Write numbers from created sudoku puzzle to file
        * @param fileName Name of file where data will be writen
        * @param matrix Matrix 9x9 that represents sudoku table
        */
       void writeSudokuInFile(char* fileName, unsigned short** matrix);

       /**
        * @brief Load data from file and convert to the matrix of Sudoku
        * @param fileName Name of file
        * @return Pointer on matrix
        */
       unsigned short** loadSudokuFromFile(char* fileName);

       /**
        * @brief Work composite actions with writing and solving sudoku
        * @param fileName name of file
        */
       void playGame(char* fileName);

};


#endif //SUDOKU_MENU_H
