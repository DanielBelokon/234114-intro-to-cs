#include <stdio.h>

#define CHARMODULO ('a' - 'A')

int main()
{
    int count = 0;  // number of occurances of search character in stream
    char schar,     // Search character - lowercase
        scharupper; // Search character - uppercase
    char curchar;   // Current character read from stream

    printf("Enter letter to count:\n");

    // set the search character and continue if alphabetical
    if ((('A' <= (schar = getchar())) && schar <= 'Z') || ('a' <= schar && schar <= 'z'))
    {
        schar = (schar - 'A') % CHARMODULO + 'a'; // Convert to lowercase
        scharupper = schar - CHARMODULO;          // set uppercase

        printf("Enter the char sequence:\n");

        // continue reading until the required $ terminator or an EOF
        while (((curchar = getchar()) != '$') && (curchar != EOF))
            if ((curchar == schar) || (curchar == scharupper))
                count++;

        printf("The letter appeared %d times\n", count);
    }

    return 0;
}