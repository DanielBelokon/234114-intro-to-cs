#include <stdio.h>
#include <stdlib.h>

int *read_arr(int size);
int find_sorted_sum(int *arr, int size, int sum);
int find_sum(int *arr, int size, int sum);
void q_sort(int *arr, int size);
int sum_exists(int *arr, int size, int sum, int *used, int index);
void swap(int *a, int *b);

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

    int exists = find_sorted_sum(arr, size, sum);
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

int find_sorted_sum(int *arr, int size, int sum)
{
    for (int i = 0; i < size; i++)
    {

        int top = size - 1;
        int bottom = i + 1;
        int calced_sum;

        while (bottom < top)
        {
            calced_sum = arr[bottom] + arr[i] + arr[top];
            if (calced_sum == sum)
                return 1;

            if (calced_sum < sum)
                bottom++;
            else
                top--;
        }
    }

    return 0;
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

void q_sort(int *arr, int size)
{
    int low = 1, high = size;

    if (size < 2)
        return;

    while (high > low)
    {
        while (arr[high] >= arr[0] && high >= low)
            high--;
        while (arr[low] <= arr[0] && low <= high)
            low++;

        if (high > low)
            swap(&arr[low++], &arr[high--]);
    }

    swap(&arr[high], &arr[0]);

    q_sort(arr, high);
    q_sort(arr + high + 1, size - high - 1);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
