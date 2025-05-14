/**
 * @file Sudoku9.h
 * @brief Declaration of Sudoku9 class for creating Sudoku puzzle 9x9 and solving it
 * @author Matija Šeremet
 * @date 25.12.2023.
 */

#ifndef SUDOKU_SUDOKU9_H
#define SUDOKU_SUDOKU9_H

/**
 * @class Sudoku9
 * @brief Contains fields of sudoku puzzle and all needed actions for solving it
 */
 class Sudoku9 {
 private:
     //only numbers 1-9
     unsigned short** matrix;

     //number of filled places in sudoku
     unsigned short generatedPlaces;
     //number of right filled places after finished game
     unsigned short rightPlaces;

 public:
     static int gameNumber;
     /**
      * @brief Sudoku9 constructor with no params that reserves memory for matrix
      */
     Sudoku9();

     /**
      * @brief Constructor for sudoku with param
      * @param iMatrix initial matrix
      */
     Sudoku9(unsigned short** iMatrix);

     /**
      * @brief Copy constructor for sudoku puzzle
      * @param other Sudoku9 object which will be copied
      */
      Sudoku9(const Sudoku9& other);

      /**
       * @brief Sudoku destructor (destroys each line in matrix and than array of pointers on these lines)
       */
      ~Sudoku9();

      /**
       * @brief Get function for matrix
       * @return pointer to matrix of sudoku
       */
      unsigned short** getMatrix() {
          return matrix;
      }

      /**
       * @brief Get function for generatedPlaces
       * @return number of generated places
       */
      unsigned short getGeneratedPlaces();

     /**
      * @brief Get function for rightPlaces
      * @return number of right filled places
      */
     unsigned short getRightPlaces();

     /**
      * @brief Set function for number of generated places
      * @param v new value
      */
     void setGeneratedPlaces(unsigned short v);

     /**
      * @brief Set function for number of right places
      * @param v new value
      */
     void setRightPlaces(unsigned short v);

     void setMatrix(unsigned short **m);

      /**
       * @brief Print each number from Sudoku table on console separating them with "|"
       */
      void printSudokuTable();

      /**
       * @brief Generate random sudoku 9x9 that should be solved and fill the matrix
       */
      void generateSudokuPuzzle();

      /**
       * @brief Check if box 3x3 contains number num
       * @param row Ordinal number of the row (0 - 8)
       * @param col Ordinal number of the column (0 - 8)
       * @param num Number which will potentially be added on position (row, col)
       * @return False if the same number is already in the box, else: true
       */
      bool unusedInBox(int row, int col, unsigned short num);

      /**
       * @brief Check if row i is regular - is number num already appears in this row
       * @param i Ordinal number of the row (0 - 8)
       * @param num Number which will potentially be added in row i
       * @return False if the same number is already in the row, else: true
       */
      bool unusedInRow(int i, int num);

     /**
     * @brief Check if column j is regular - is number num already appears in this column
     * @param j Ordinal number of the column (0 - 8)
     * @param num Number which will potentially be added in column j
     * @return False if the same number is already in the column, else: true
     */
     bool unusedInCol(int j, int num);

     /**
      * @brief Check if last 3 conditions are satisfied
      * @param i Ordinal number of the row (0 - 8)
      * @param j Ordinal number of the column (0 - 8)
      * @param num Number which will potentially be added on position (i, j)
      * @return True if all of 3 last conditions are satisfied
      */
     bool checkIfSafe(int i, int j, int num);

     /**
      * @brief Fill all other fields except these ones on the main diagonal
      * @param i Ordinal number of the row (0 - 8)
      * @param j Ordinal number of the column (0 - 8)
      * @return True if position (i, j) was successfully filled
      */
     bool fillRemaining(int i, int j);

     /**
      * @brief Remove 28-48 digits from the puzzle for the user to fill them
      */
     void removeDigits();

     /**
      * @brief Find the first unfilled location (value is 0) and set current values of row and column on it
      * @param row Ordinal number of the row (0 - 8)
      * @param col Ordinal number of the column (0 - 8)
      * @return False if no unassigned entries remain
      */
     bool findUnassignedLocation(int& row, int& col);

     /**
      * @return If sudoku is solved or not
      */
     bool solveSudoku();

     /**
      * @brief Check if each digit from sudoku puzzle is in interval 1-9
      * @return True if all right
      */
     bool isInRange();

     /**
      * @brief Check if sudoku is valid solved
      * @return True if all right
      */
     bool isSudokuValid();

     /**
      * @brief Check if user's created unsolved sudoku is valid
      * @param fileName Name of file
      * @param usersGeneratedPlaces generated places in case user created a puzzle
      * @return True if all right
      */
     bool isUnsolvedSudokuValid(char *fileName, unsigned short& usersGeneratedPlaces);

     /**
      * @brief Shows how many fields are right
      * @param solved Represents one example of well solved sudoku
      */
     void evaluateSudoku(Sudoku9& solved);
 };


#endif //SUDOKU_SUDOKU9_H
