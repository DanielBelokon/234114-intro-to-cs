#include <stdio.h>

#define CHARMODULO 32

int main()
{
    int count = 0;  // number of occurances of search character in stream
    char schar,     // Search character - lowercase
        scharupper; // Search character - uppercase
    char curchar;   // Current character read from stream

    printf("Enter letter to count:\n");

    // set the search character and continue if alphabetical
    if (('A' <= (schar = getchar())) && (schar <= 'z'))
    {
        schar = (schar - 'A') % CHARMODULO + 'a'; // Convert to lowercase
        scharupper = schar + 'A' - 'a';           // set uppercase

        printf("Enter the char sequence:\n");

        // continue reading until the required $ terminator or the standard null terminator is encountered
        while (((curchar = getchar()) != '$') && (curchar != '\0'))
        {
            if ((curchar == schar) || (curchar == scharupper))
                count++;
        }
        printf("The letter appeared %d times\n", count);
    }

    return 0;
}