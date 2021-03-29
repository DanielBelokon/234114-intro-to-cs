#include <stdio.h>

int main()
{
    putchar('H');
    putchar('\n');
    int c;
    while ((c = getchar()) != EOF)
    {
        if (c == '\b')
        {
            putchar('\\');
            c = 'b';
        }
        putchar(c);
    }

    putchar(EOF);

    return 0;
}