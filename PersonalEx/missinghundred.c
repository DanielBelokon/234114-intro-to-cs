#include <stdio.h>

#define ARRSIZE 100

int main()
{
    int numbers[ARRSIZE] = {0};

    for (int i = 0; i < ARRSIZE; i++)
    {
        if (i != 50)
            numbers[i] = i + 1;
    }

    int index = ARRSIZE / 2;
    int sum = 0;
    for (int i = 0; i < ARRSIZE; i++)
    {
        sum += numbers[i];
    }

    printf("%d", (5050 - sum));

    return 0;
}