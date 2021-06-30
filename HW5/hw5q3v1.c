#include <stdio.h>
#include <stdlib.h>

int *read_arr(int size);

int find_sum(int *arr, int size, int sum);
int sum_exists(int *arr, int size, int sum, int *used, int index);

int main()
{
    int size, sum;
    int *arr;

    printf("Please enter length:\n");
    if (scanf("%d", &size) != 1)
        return 1;

    printf("Please enter array:\n");
    if ((arr = read_arr(size)) == NULL)
        return -1;

    printf("Please enter sum:\n");
    if (scanf("%d", &sum) != 1)
        return 1;

    q_sort(arr, size - 1);

    // for (int i = 0; i < size; i++)
    // {
    //     printf("%d ", arr[i]);
    // }

    int exists = find_sum(arr, size, sum);
    if (!exists)
        printf("Such elements do not exist.");
    else
        printf("Such elements do exist.");

    free(arr);
    return 0;
}

int *read_arr(int size)
{
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL)
        return arr;

    for (int i = 0; i < size; i++)
    {
        if (scanf("%d", arr + i) != 1)
        {
            free(arr);
            return NULL;
        }
    }

    return arr;
}

int find_sum(int *arr, int size, int sum)
{
    int *used = (int *)malloc(size * sizeof(int));
    if (used == NULL)
        return -1;

    for (int i = 0; i < size; i++)
        used[i] = 0;

    int exists = sum_exists(arr, size, sum, used, 0);
    free(used);
    return exists;
}

int sum_exists(int *arr, int size, int sum, int *used, int index)
{
    if (sum == 0 && index == 3)
        return 1;
    if (index >= 3)
        return 0;

    for (int i = 0; i < size; i++)
    {
        if (used[i])
            continue;

        used[i] = 1;
        if (sum_exists(arr, size, sum - arr[i], used, index + 1))
            return 1;
        used[i] = 0;
    }

    return 0;
}
