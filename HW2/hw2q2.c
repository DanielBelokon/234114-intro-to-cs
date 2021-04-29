/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

void printThreeDigitsOpenMessage();
void printResults(int avg, int rootOfMinNum, int avgPowTwoRootOfMinNum);
void printCharactersOpenMessage();
void printDataPerGivenCharAsInput(char ch, int numberOfTimesAppeared);
void printNumberOfOtherCharsAppeared(int numberOfOtherCharsAppeared);

int average(int, int, int);
int min(double, double);
int absolute(double);
double root(double);
double power(double base, int power);
int characterAnalysis();

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{

    return 0;
}

/**/

int average(int a, int b, int c)
{
    return (a + b + c) / 3; // the return type is an int so it trucates it
}

int min(double a, double b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int absolute(double num)
{
    if (num >= 0)
        return num;
    else
        return -num;
}

double root(double num)
{
    for (int i = 0; i < num; i++)
    {
        /* code */
    }
    
}

double power(double base, int power)
{
    if (base < 0 || power < 0)
        return -1;

    if (power == 0)
        return 1;
        
    while(power-- > 0)
    {
        base *= base;
    }

    return base;
}

int characterAnalysis()
{
    return 0;
}

/**/

void printThreeDigitsOpenMessage()
{
    printf("Please enter three integers:\n");
}

void printResults(int avg, int rootOfMinNum, int avgPowTwoRootOfMinNum){
    printf("%d %d %d\n", avg, rootOfMinNum,avgPowTwoRootOfMinNum);
}


void printCharactersOpenMessage(){
    printf("Please enter your character set:\n");
}

void printDataPerGivenCharAsInput(char ch, int numberOfTimesAppeared){
    printf(
        "letter %c appeared %d time in the given set of characters\n",
        ch, numberOfTimesAppeared
    );
}
void printNumberOfOtherCharsAppeared(int numberOfOtherCharsAppeared){
    printf(
        "number of other characters in the given set was: %d\n",
        numberOfOtherCharsAppeared
    );
}
