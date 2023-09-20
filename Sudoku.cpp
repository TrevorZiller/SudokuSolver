#include <iostream>
using namespace std;

// size of sudoku, 9x9
#define N 9

// Function to print the Sudoku
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        } //for
        cout << endl;
    } //for
} //printGrid

// Function to check if it's safe to place a number at the given (row, col) position
bool canPlace(int grid[N][N], int row, int col, int num) {
    // Check if the number is already present in the current row or column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        } //if
    } //for

    // Check if the number is already present in the current 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            } //if
        } //for
    } //for

    return true;
} //canPlace

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Check for an empty cell
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            } //if
        } //for
        if (isEmpty) {
            break;
        } //if
    } //for

    // If no empty cell is found, the puzzle is solved
    if (!isEmpty) {
        return true;
    } //if

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (canPlace(grid, row, col, num)) {
            // Place the number if it's safe
            grid[row][col] = num;

            // Recursively solve the rest of the puzzle
            if (solveSudoku(grid)) {
                return true;
            } //if

            // If the placement doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        } //if
    } //for

    return false;
} //solveSudoku

int main() {
    //follow with any grid in this format, 0 means empty square.
    //will print the grid if there is a solution, or none if no solution exists or its ambiguous
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku solution:\n";
        printGrid(grid);
    } //if 
    else {
        cout << "No solution exists.\n";
    } //else

    return 0;
} //main