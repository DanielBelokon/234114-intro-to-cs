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
int isRowValid(int row[], int grid_size);
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

    // check if input is invalid (no whole root/non-positive grid_size)
    // while (scanf(" %d", &grid_size) != 1 ||
    //        grid_size <= 0 ||
    //        (subgrid_size = root(grid_size)) < 0)
    //     ;

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
        if (!isRowValid(sudoku_arr[i], grid_size) ||
            !isColValid(sudoku_arr, i, grid_size) ||
            !isSubgridValid(sudoku_arr, i, subgrid_size))
        {
            return 0;
        }
    }
    return 1;
}

int isRowValid(int row[MAX_SIZE], int grid_size)
{
    int nums[MAX_SIZE + 1] = {0};

    // Iterate and check for duplicates by, save occurances in the num array
    for (int i = 0; i < grid_size; i++)
    {
        int val = row[i];

        if (!nums[val])
            nums[val] = 1;
        else
            return 0;
    }
    // Row is valid
    return 1;
}

int isColValid(int sudoku_arr[][MAX_SIZE], int col, int grid_size)
{
    int nums[MAX_SIZE + 1] = {0};

    // Iterate and check for duplicates by, save occurances in the num array
    for (int i = 0; i < grid_size; i++)
    {
        int val = sudoku_arr[i][col];

        if (!nums[val])
            nums[val] = 1;
        else
            return 0;
    }
    // Col is valid
    return 1;
}

int isSubgridValid(int sudoku_arr[MAX_SIZE][MAX_SIZE],
                   int index, int subgrid_size)
{
    int nums[MAX_SIZE + 1] = {0};
    int row_shift = (index / subgrid_size) * subgrid_size,
        col_shift = (index % subgrid_size) * subgrid_size;

    for (int row = 0; row < subgrid_size; row++)
    {
        for (int col = 0; col < subgrid_size; col++)
        {
            int val = sudoku_arr[row + row_shift][col + col_shift];

            if (!nums[val])
                nums[val] = 1;
            else
                return 0;
        }
    }

    return 1;
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
