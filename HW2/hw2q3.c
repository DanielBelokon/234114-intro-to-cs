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

int getInput(int sudoku[MAX_SIZE][MAX_SIZE], int size);

int isRowValid(int row[MAX_SIZE], int size);
int isColValid(int sudoku[MAX_SIZE][MAX_SIZE], int col, int size);
int isInnerSquareValid(int sudoku[MAX_SIZE][MAX_SIZE],
                       int index, int size, int smallN);

void printOpenMessageForSudokuSize();
void printOpenMessageForSudokuSolution();
void printValidSolution();
void printBadSolution();

/*-------------------------------------------------------------------------
    The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int sudokuarr[MAX_SIZE][MAX_SIZE] = {{0}};
    int n, smallN = 0; // the sudoku size and it's root ("smaller squares")

    printOpenMessageForSudokuSize();

    // check if input is invalid (no whole root/non-positive n)
    while (scanf(" %d", &n) != 1 || n <= 0 || (smallN = root(n)) < 0)
        ;

    printOpenMessageForSudokuSolution();

    if (getInput(sudokuarr, n))
        return 1;

    // Check if the solution is valid
    for (int i = 0; i < n; i++)
    {
        if (!isRowValid(sudokuarr[i], n) ||
            !isColValid(sudokuarr, i, n) ||
            !isInnerSquareValid(sudokuarr, i, n, smallN))
        {
            printBadSolution();
            return 0;
        }
    }
    // If we got this far, we got ourselves a solution
    printValidSolution();

    return 0;
}

int getInput(int sudoku[MAX_SIZE][MAX_SIZE], int actualSize)
{
    for (int row = 0; row < actualSize; row++)
    {
        for (int col = 0; col < actualSize; col++)
        {
            if (scanf(" %d", &(sudoku[row][col])) != 1)
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

int isRowValid(int row[MAX_SIZE], int actualSize)
{
    int nums[10] = {0};

    // Iterate and check for duplicates by, save occurances in the num array
    for (int i = 0; i < actualSize; i++)
    {
        int val = row[i];

        if (!nums[val])
            nums[val] = 1;
        else
            // Row isn't valid
            return 0;
    }
    // Row is valid
    return 1;
}

int isColValid(int sudoku[MAX_SIZE][MAX_SIZE], int col, int actualSize)
{
    int nums[10] = {0};

    // Iterate and check for duplicates by, save occurances in the num array
    for (int i = 0; i < actualSize; i++)
    {
        int val = sudoku[i][col];

        if (!nums[val])
            nums[val] = 1;
        else
            // Col isn't valid
            return 0;
    }
    // Col is valid
    return 1;
}

int isInnerSquareValid(int sudoku[MAX_SIZE][MAX_SIZE],
                       int index, int actualSize, int smallN)
{
    int nums[10] = {0};
    int rowshift = (index / smallN) * smallN,
        colshift = (index % smallN) * smallN;

    for (int row = 0; row < smallN; row++)
    {
        for (int col = 0; col < smallN; col++)
        {
            int val = sudoku[row + rowshift][col + colshift];

            if (!nums[val])
                nums[val] = 1;
            else
                // Col isn't valid
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
