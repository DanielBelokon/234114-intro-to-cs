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

int root(int);

int getGridInput(int sudoku_arr[MAX_SIZE][MAX_SIZE], int grid_size);

int isSolved(int sudoku_arr[MAX_SIZE][MAX_SIZE],
             int grid_size, int subgrid_size);

// Functions used by isSolved
int isRowValid(int sudoku_arr[][MAX_SIZE], int row, int grid_size);
int isColValid(int sudoku_arr[][MAX_SIZE], int col, int grid_size);
int isSubgridValid(int sudoku_arr[][MAX_SIZE], int index, int subgrid_size);

// Function used by all validity checks
int isNotDuplicate(int sudoku_arr[][MAX_SIZE], int row_shift,
                   int col_shift, int row_iter, int col_iter);

void printOpenMessageForSudokuSize();
void printOpenMessageForSudokuSolution();
void printValidSolution();
void printBadSolution();

/*-------------------------------------------------------------------------
    Given a sudoku grid size followed by the populated grid, 
    validate the solution and print out the results.
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
    } while (grid_size <= 0 || subgrid_size <= 0 || grid_size > MAX_SIZE);

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

/**/

/* 
    Store input in the given array, use only grid_size*grid_size elements

    sudoku_arr:     the sudoku grid to store input in
    grid_size:      sudoku size

    Returns:        0 on success, -1 on invalid input
*/
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
    if (num == 0)
        return num;

    for (int i = 1; i <= num; i++)
    {
        if (num == i * i)
            return i;
        else if (num / i < i)
            break;
    }
    return -1;
}

/*  
  Check if the sudoku grid is valid (no duplicates in row, col, subgrid)

  sudoku_arr:       the sudoku grid to check
  grid_size:        sudoku size
  subgrid_size:     sqrt of sudoku size (subgrids)

  returns:          1 if solution is valid, 0 if invalid
*/
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

/*  
  General duplicate checker used by valid checks (all are very similar)
  Check if a number appears twice in the given range (row X col)

  sudoku_arr:  the sudoku grid to check
  row_shift:   the initial position from which to iterate over rows
  col_shift:   the initial position from which to iterate over columns
  col_iter:    number of iterations over the columns
  row_iter:    number of iterations over the rows
 
  Returns:     0 if duplicate, 1 if no duplicates found
 */
int isNotDuplicate(int sudoku_arr[][MAX_SIZE], int row_shift,
                   int col_shift, int row_iter, int col_iter)
{
    // Keep track of occurences
    int num_occured[MAX_SIZE + 1] = {0};

    // Validate parameters
    if (row_iter > MAX_SIZE || col_iter > MAX_SIZE ||
        col_shift > MAX_SIZE || row_iter > MAX_SIZE)
        return -1;

    // Iterate over the 2D array per the parameters passed
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

    // If we got here, there are no duplicates
    return 1;
}

/*  
  Checks for duplicate numbers in a given row

  sudoku_arr:     the sudoku grid to check
  row:            index of the row to check
  grid_size:      sudoku size (length of the row)
 
  Returns:        0 if invalid, 1 if valid
*/
int isRowValid(int sudoku_arr[][MAX_SIZE], int row, int grid_size)
{
    // shift to current row, don't shift columns (we iterate over them)
    // iterate over a single row (the one we're checking), iterate over cols
    return isNotDuplicate(sudoku_arr, row, 0, 1, grid_size);
}

/*  
  Checks for duplicate numbers in a given column

  sudoku_arr:     the sudoku grid to check
  col:            index of the column to check
  grid_size:      sudoku size (length of the column)
 
  Returns:        0 if invalid, 1 if valid
*/
int isColValid(int sudoku_arr[][MAX_SIZE], int col, int grid_size)
{
    // don't shift rows (we iterate over them), shift to current column
    // iterate over all rows in the col, only go over the one row
    return isNotDuplicate(sudoku_arr, 0, col, grid_size, 1);
}

/*  
  Checks for duplicate numbers in a given row

  sudoku_arr:     the sudoku grid to check
  index:          the index of the subgrid (counted row by row, LTR)
  subgrid_size:   the length of the rows & columns in the subgrid
 
  Returns:        0 if invalid, 1 if valid
*/
int isSubgridValid(int sudoku_arr[MAX_SIZE][MAX_SIZE],
                   int index, int subgrid_size)
{

    // there are subgrid_size subgrids in a row,
    // if we "overflowed", move index/n rows down (lose the remainder)
    int row_shift = (index / subgrid_size) * subgrid_size,
        // the remainder is the subgrid index in the current row
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
