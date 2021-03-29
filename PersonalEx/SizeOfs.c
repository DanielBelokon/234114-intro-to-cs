#include <stdio.h>
#define typeAmount 7

int main()
{
    int sizes[typeAmount];
    sizes[0] = sizeof(char);
    sizes[1] = sizeof(short);
    sizes[2] = sizeof(int);
    sizes[3] = sizeof(long);
    sizes[4] = sizeof(float);
    sizes[5] = sizeof(double);
    sizes[6] = sizeof(void *);

    for (int i = 0; i < typeAmount; i++)
    {
        printf("%d\n", sizes[i]);
    }

    return 0;
}