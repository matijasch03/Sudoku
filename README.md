# Sudoku

The project task from the course object oriented programming (2) done in program language c++  
Interactive console game for playing sudoku

---

## 📌 Project Overview

Congratulations on advancing to the semifinals of the **"Sudokusfera"** quiz!  
Now it’s time to take on the key challenge – the **"Sudoku Challenge"**.  
In this task, you’ll tackle Sudoku puzzles with a 9x9 board, consisting of 3x3 subgrids.

### 🎯 Game Rules

Each digit from **1 to 9** must appear **exactly once** in:
- Each row of the board
- Each column of the board
- Each 3x3 subgrid

---

## 🎮 Game Flow

1. Launch the program through a **console menu**.
2. The menu offers options to:
   - Load an existing Sudoku puzzle from a file
   - Generate a new Sudoku puzzle (which is saved to a file for inspection)
3. Choose whether to:
   - Solve the puzzle manually (by loading a solution file), or
   - Let the program solve the puzzle automatically
4. After solving:
   - The app displays **statistics** such as:
     - Number of correct entries
     - Number of incorrect entries
     - Current game number
5. Option to start a **new game iteration**

---

## ✅ Functional Requirements

The program supports the following:

### 1. Command Line Arguments
- Accept file names via command-line arguments.

### 2. Load Sudoku Puzzle
- Read a 9x9 Sudoku board from a text file.
- The file may contain either a full solution or an incomplete puzzle.

### 3. Save Sudoku Puzzle
- Write the board to a text file in a clear, human-readable format.

### 4. Validate User Solution
- Check if the solution follows Sudoku rules for:
  - Rows
  - Columns
  - 3x3 subgrids

### 5. Auto-Solve Puzzle
- Provide a correct solution by implementing a solving algorithm.

### 6. Puzzle Generation
- Generate a valid 9x9 Sudoku puzzle.
- Each 3x3 subgrid has no more than 6 filled cells on average.

---

## 🧱 Implementation Details

### Core Class: `Sudoku9`
- Central class containing:
  - 9x9 matrix representation of the board
  - Member variables like correct entry counter, game counter, etc.

### Required Modules
1. Class representing the puzzle board (`Sudoku`)
2. File reading and writing
3. Validation logic
4. Puzzle-solving algorithm
5. Puzzle generation logic
6. Game statistics handling

---

## 🧪 Testing

- Test with both typical and **edge-case** inputs.
- Check for:
  - Correct parsing
  - Valid and invalid solutions
  - Puzzle generation accuracy

---

## 🧑‍💻 Coding Style

- Each `.cpp` and `.h` file include:
  - Short description
  - Author(s)
  - Last modified date
- Comment all:
  - Key functions
  - Class members
  - Attributes
- Maintain:
  - Clean indentation
  - Descriptive naming
  - Line length under control

---

## 📄 Report

The project report (`Izvestaj.pdf`) includes a detailed description of the whole project.
