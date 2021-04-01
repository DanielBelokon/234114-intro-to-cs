#include <stdio.h>

#define MAX_LINE 1024
#define TAB_LENGTH 4
#define TABSTOP_LENGTH 10

int GetLine();

int main()
{
    GetLine();
    return 0;
}

int GetLine()
{
    char current;
    int index = 0;
    int column_index = 0;
    char line[MAX_LINE];

    while ((current = getchar()) != EOF)
    {
        if (current == '\n')
            column_index = 0;
        // If tab detected - go to next column determined by the tab stop length
        else
        {
            // If it's not a new line - update the column index regarding current line
            column_index = (column_index + 1) % (TABSTOP_LENGTH);

            // replace tab by iterating an extra TABSTOP_LENGTH - 1 times
            // final one is set with current outside all the conditionals
            if (current == '\t')
            {
                for (int t = column_index; t < TABSTOP_LENGTH; t++)
                {
                    line[index++] = ' ';
                }
                current = '|';
                column_index = 0;
            }
        }

        line[index++] = current;
    }
    printf(line);

    return 0;
}