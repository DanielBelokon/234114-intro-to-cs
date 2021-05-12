#include <stdio.h>

void swap(int *px, int *py)
{
    int temp = *px;
    *px = *py;
    *py = temp;
}

int main()
{
    int x = 5, y = 7;
    swap(&x, &y);
    return 0;
}