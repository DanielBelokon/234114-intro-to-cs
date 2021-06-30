#include <stdio.h>
#include <stdlib.h>

int *read_arr(int size);
int tri_sum_exists(int *arr, int size, int sum);
int find_sum(int *arr, int size, int sum);
void q_sort(int *arr, int size);
int sum_exists(int *arr, int size, int sum, int *used, int index);
void swap(int *a, int *b);

int main()
{
    int size, sum;
    int *arr;

    // Get input, exit if invalid or no mem left
    printf("Please enter length:\n");
    if (scanf("%d", &size) != 1)
        return 1;

    printf("Please enter array:\n");
    if ((arr = read_arr(size)) == NULL)
        return -1;

    printf("Please enter sum:\n");
    if (scanf("%d", &sum) != 1)
        return 1;

    // Sort for faster searching
    q_sort(arr, size - 1);


    if (!tri_sum_exists(arr, size, sum))
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

/* Find the sum of 3 using quick-sort style indexing:
* Use each element as pivot one at a time, determin with two indices (top and bottom) if
* three numbers make up a sum by decreasing or increasing it accordingly,
* if not - continue to next pivot, O(n^2) worst case
*/
int tri_sum_exists(int *arr, int size, int sum)
{
    for (int i = 0; i < size; i++)
    {

        int top = size - 1;
        int bottom = i + 1;
        int calced_sum;

        while (bottom < top)
        {
            calced_sum = arr[i] + arr[bottom] + arr[top];

            // Found solution
            if (calced_sum == sum)
                return 1;

            // Decrease or increase the sum accordingly (array is sorted)
            if (calced_sum < sum)
                bottom++;
            else
                top--;
        }
    }

    // No solution was found
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
