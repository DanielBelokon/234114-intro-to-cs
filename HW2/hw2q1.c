/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define SPACE_INDEX 0
#define ALPHA_INDEX 1
#define NMRCAL_INDEX 2

#define CHAR_TYPES_AMNT 3 // The amount of different char 'types' (array size)

void printGivenParamsToTheOutput(
    char ch, int asciiCode, int asciiCodePowTwo,
    int difference, int unitDigitOfDiff
);

void determinCharType(char ch, int chTypeCntArr[CHAR_TYPES_AMNT]);

void printResults(int digitsCounter, int lettersCounter, int spacesCounter);

/*-------------------------------------------------------------------------
  Print character ascii information
  Upon receiving a stream of characters, iterate over it and print the ascii
  representation, it's square, differaence to the previous char, and the
  first digit of the differance. 
  Upon completion print the summation of specific character types recieved
 -------------------------------------------------------------------------*/
int main()
{
    unsigned char ch = 0;                    // current char read
    int prev = 0;                            // previous ch
    int chTypeCntArr[CHAR_TYPES_AMNT] = {0}; // char type counter array by index

    // iterate over the input stream and print ascii info while valid
    while (scanf("%c", &ch) == 1 && ch != ';')
    {
        int difference = ch - prev;
        printGivenParamsToTheOutput(ch, (int)ch, ch * (int)ch,
                                    difference, difference % 10);

        determinCharType(ch, chTypeCntArr);
        prev = ch;
    }

    printResults(chTypeCntArr[NMRCAL_INDEX],
                 chTypeCntArr[ALPHA_INDEX],
                 chTypeCntArr[SPACE_INDEX]);

    return 0;
}

/*
    Update the indexed counters of the passed array by using the int variable
    Counter indexes are derived from TYPE_INDEX preproccesor definitions

    ch - the character to test
    chTypeCntArr - the array to increment with the character type of ch
*/
void determinCharType(char ch, int chTypeCntArr[CHAR_TYPES_AMNT])
{
    chTypeCntArr[SPACE_INDEX] += ch == ' ';
    chTypeCntArr[ALPHA_INDEX] += ((ch <= 'Z' && ch >= 'A') ||
                                  (ch <= 'z' && ch >= 'a'));
    chTypeCntArr[NMRCAL_INDEX] += (ch <= '9' && ch >= '0');
}

void printGivenParamsToTheOutput(
    char ch, int asciiCode, int asciiCodePowTwo,
    int difference, int unitDigitOfDiff)
{
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
