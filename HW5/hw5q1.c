#include <stdio.h>
#include <limits.h>

int find_largest(int nums_left, int cur_largest, int second_largest);

int main()
{
    int iterations = 0;
    int second_largest = 0;
    printf("Please enter length:\n");
    if (scanf("%d", &iterations) > 0)
    {
        printf("Please enter array:\n");
        second_largest = find_largest(iterations, INT_MIN, INT_MIN);
        printf("The second-greatest is:\n%d", second_largest);
    }

    return 0;
}

int find_largest(int nums_left, int cur_largest, int second_largest)
{
    if (nums_left == 0)
        return second_largest;

    int num = 0;

    if (scanf("%d", &num) > 0)
    {
        if (num > cur_largest)
        {
            return find_largest(--nums_left, num, cur_largest);
        }
        else if (num > second_largest)
            return find_largest(--nums_left, cur_largest, num);
    }

    return find_largest(--nums_left, cur_largest, second_largest);
}