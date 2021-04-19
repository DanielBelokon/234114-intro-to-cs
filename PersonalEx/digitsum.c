#include <stdio.h>

int main()
{
    while (1)
    {
        int num;
        int sum = 0;
        if (!scanf("%d", &num))
            return 1;

        while (num > 0)
        {
            sum += num % 10;
            num /= 10;
        }

        printf("%d\n", sum);
    }

    return 0;
}