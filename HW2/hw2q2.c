/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/

void printThreeDigitsOpenMessage();
void printResults(int avg, int rootOfMinNum, int avgPowTwoRootOfMinNum);
void printCharactersOpenMessage();
void printDataPerGivenCharAsInput(char ch, int numberOfTimesAppeared);
void printNumberOfOtherCharsAppeared(int numberOfOtherCharsAppeared);


/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{

    return 0;
}

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
