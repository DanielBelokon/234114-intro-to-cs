#include <stdio.h>

int main()
{
    int c = 0;
    printf("F\tC\n");
    for (int f = 0; f <= 300; f += 20)
    {
        printf("%3d\t%5.1f\n", f, 5.0 * (f - 32.0) / 9.0);
    }

    return 0;
}