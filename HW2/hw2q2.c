/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/
#define ALPHABET_LEN ('z' - 'a' + 1)
#define MAX_POW 1000000000

void printThreeDigitsOpenMessage();
void printResults(int avg, int rootOfMinNum, int avgPowTwoRootOfMinNum);
void printCharactersOpenMessage();
void printDataPerGivenCharAsInput(char ch, int numberOfTimesAppeared);
void printNumberOfOtherCharsAppeared(int numberOfOtherCharsAppeared);

int average(int, int, int);
int min(int, int);
int absolute(int);
int root(int);
int power(int base, int power);
int characterAnalysis();

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    printThreeDigitsOpenMessage();
    int a, b, c;
    int numminabs, numaverage, numroot;

    if (scanf(" %d%d%d", &a, &b, &c) != 3)
        return -1;

    numminabs = absolute(min(min(a, b), c));
    numaverage = average(a, b, c);
    numroot = root(numminabs);

    printResults(numaverage, numroot, power(numaverage, numminabs));
    characterAnalysis();
    return 0;
}

/**/

int average(int a, int b, int c)
{
    return (a + b + c) / 3.0; // the return type is an int so it trucates it
}

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int absolute(int num)
{
    if (num < 0)
        return -num;
    else
        return num;
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

int power(int base, int power)
{
    int res = 1;
    if (base < 0 || power < 0)
        return -1;

    if (base == 0)
        return base;

    while (power-- > 0)
    {
        if (base > MAX_POW / base)
            return -1;

        res *= base;
    }

    return res;
}

int characterAnalysis()
{
    printCharactersOpenMessage();
    char ch = 0;
    char alpha_cnt_arr[ALPHABET_LEN] = {0};

    int other_char_cnt = 0;

    while (scanf("%c", &ch) != EOF)
    {
        if (ch >= 'a' && ch <= 'z')
            alpha_cnt_arr[ch - 'a']++;
        else
            // Count all characters except newline and carriage return
            other_char_cnt += (ch != '\n' && ch != '\r');
    }

    for (int i = 0; i < ALPHABET_LEN; i++)
    {
        printDataPerGivenCharAsInput(i + 'a', alpha_cnt_arr[i]);
    }
    printNumberOfOtherCharsAppeared(other_char_cnt);
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
