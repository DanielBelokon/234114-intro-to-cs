/*-------------------------------------------------------------------------
    Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*=========================================================================
    Constants and definitions:
==========================================================================*/

#define MAX_SIZE 25

int validateInput(int);
int root(int);

int getGridInput(int sudoku_arr[MAX_SIZE][MAX_SIZE], int grid_size);

int isSolved(int sudoku_arr[MAX_SIZE][MAX_SIZE],
             int grid_size, int subgrid_size);

// Functions used by isSolved
int isRowValid(int sudoku_arr[][MAX_SIZE], int row, int grid_size);
int isColValid(int sudoku_arr[][MAX_SIZE], int col, int grid_size);
int isSubgridValid(int sudoku_arr[][MAX_SIZE], int index, int subgrid_size);

void printOpenMessageForSudokuSize();
void printOpenMessageForSudokuSolution();
void printValidSolution();
void printBadSolution();

/*-------------------------------------------------------------------------
    The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int sudoku_arr[MAX_SIZE][MAX_SIZE] = {{0}};
    int grid_size = 0, subgrid_size = 0;

    printOpenMessageForSudokuSize();

    do
    {
        if (scanf(" %d", &grid_size) != 1)
            return -1;
        subgrid_size = root(grid_size);
    } while (grid_size <= 0 || subgrid_size <= 0);

    // get the input (we assume it's valid per the doc)
    printOpenMessageForSudokuSolution();
    getGridInput(sudoku_arr, grid_size);

    // Check if the solution is valid
    if (isSolved(sudoku_arr, grid_size, subgrid_size))
        printValidSolution();
    else
        printBadSolution();

    return 0;
}

// Store input in the given array, use only grid_size*grid_size elements
// Returns 0 on success, -1 on invalid input
int getGridInput(int sudoku_arr[MAX_SIZE][MAX_SIZE], int grid_size)
{
    for (int row = 0; row < grid_size; row++)
    {
        for (int col = 0; col < grid_size; col++)
        {
            if (scanf(" %d", &(sudoku_arr[row][col])) != 1)
                return -1;
        }
    }
    return 0;
}

int root(int num)
{
    for (int i = 1; i <= num; i++)
    {
        if (num == i * i)
            return i;
        else if (num / i < i)
            break;
    }
    return -1;
}

int isSolved(int sudoku_arr[][MAX_SIZE], int grid_size, int subgrid_size)
{
    for (int i = 0; i < grid_size; i++)
    {
        if (!isRowValid(sudoku_arr, i, grid_size) ||
            !isColValid(sudoku_arr, i, grid_size) ||
            !isSubgridValid(sudoku_arr, i, subgrid_size))
        {
            return 0;
        }
    }
    return 1;
}

/*  General duplicate checker (all the duplication checks are very similar)
 *  sudoku_arr - the sudoku grid to check
 *  row_shift - the initial position from which to iterate over rows
 *  col_shift - the initial position from which to iterate over columns
 *  col_iter - number of iterations over the columns
 *  row_iter - number of iterations over the rows
 */
int isNotDuplicate(int sudoku_arr[][MAX_SIZE], int row_shift,
                   int col_shift, int row_iter, int col_iter)
{
    // Keep track of occurences
    int num_occured[MAX_SIZE + 1] = {0};

    if (row_iter > MAX_SIZE && col_iter > MAX_SIZE &&
        col_shift > MAX_SIZE && row_iter > MAX_SIZE)
        return -1;

    for (int row = 0; row < row_iter; row++)
    {
        for (int col = 0; col < col_iter; col++)
        {
            int val = sudoku_arr[row + row_shift][col + col_shift];

            // If number is new, set to occured. If occured, return duplicate
            if (num_occured[val])
                return 0;

            num_occured[val] = 1;
        }
    }

    return 1;
}

int isRowValid(int sudoku_arr[][MAX_SIZE], int row, int grid_size)
{
    // isNotDuplicate is called with the following parameters:
    // Shift row index (this chooses the correct row)
    // Don't shift the columns (we iterate over them),
    // Go over one row
    // Iterate over columns in that row grid_size times
    return isNotDuplicate(sudoku_arr, row, 0, 1, grid_size);
}

int isColValid(int sudoku_arr[][MAX_SIZE], int col, int grid_size)
{
    // isNotDuplicate is called with the following parameters:
    // Don't shift the rows (we iterate over them),
    // Shift column index (this chooses the correct row)
    // Iterate over rows in that column grid_size times
    // Go over one column
    return isNotDuplicate(sudoku_arr, 0, col, grid_size, 1);
}

int isSubgridValid(int sudoku_arr[MAX_SIZE][MAX_SIZE],
                   int index, int subgrid_size)
{
    //int num_occured[MAX_SIZE + 1] = {0};

    int row_shift = (index / subgrid_size) * subgrid_size,
        col_shift = (index % subgrid_size) * subgrid_size;

    // shift to appropriate subgrid, iterate over all items in it
    return isNotDuplicate(sudoku_arr,
                          row_shift, col_shift,
                          subgrid_size, subgrid_size);
}

void printOpenMessageForSudokuSize()
{
    printf("Please enter the size of your soduko:\n");
}

void printOpenMessageForSudokuSolution()
{
    printf("Please enter your solution:\n");
}

void printValidSolution()
{
    printf("Valid solution!\n");
}

void printBadSolution()
{
    printf("Bad solution!\n");
}
