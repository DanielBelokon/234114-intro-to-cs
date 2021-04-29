/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/

void printGivenParamsToTheOutput(
    char ch, int asciiCode, int asciiCodePowTwo,
    int difference, int unitDigitOfDiff
);

void printResults(int digitsCounter, int lettersCounter, int spacesCounter);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{

    return 0;
}

void printGivenParamsToTheOutput(
    char ch, int asciiCode, int asciiCodePowTwo,
    int difference, int unitDigitOfDiff
){
    printf(
        "%c%10d%10d%10d%10d\n", ch, asciiCode,
        asciiCodePowTwo, difference, unitDigitOfDiff
    );
}

void printResults(int digitsCounter, int lettersCounter, int spacesCounter){
    printf("Number of digits received: %d\n", digitsCounter);
    printf("Number of letters received: %d\n", lettersCounter);
    printf("Number of spaces received: %d\n", spacesCounter);
}
