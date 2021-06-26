#include <stdio.h>
#include <limits.h>

#define N 4

void find_shortest(int map[][N], int source, int dest, int shortest_path[]);
void print_shortest_path(int *sol, int n);
int step_shortest(int map[][N], int cur_city, int dest, int scorched[],
                  int cur_len, int cur_path[], int index, int shortest_path[]);

void arrcpy(int dest[], int source[], int size);
int read_map(int map[][N]);

int main()
{
    int map[N][N] = {{0}};
    int shortest_path[N + 2];
    int source, dest;

    printf("Please enter roads matrix:\n");
    if (read_map(map))
        return -1;

    printf("Please enter source city:\n");
    if (scanf("%d", &source) != 1)
        return -1;

    printf("Please enter destination city:\n");
    if (scanf("%d", &dest) != 1)
        return -1;

    find_shortest(map, source, dest, shortest_path);
    print_shortest_path(shortest_path, shortest_path[N]);
}

void find_shortest(int map[][N], int source, int dest, int shortest_path[])
{
    int scorched[N] = {0};
    scorched[source] = 1;
    int cur_path[N] = {source};
    shortest_path[N + 1] = INT_MAX;

    step_shortest(map, source, dest, scorched, 0, cur_path, 1, shortest_path);
}

int step_shortest(int map[][N], int cur_city, int dest, int scorched[],
                  int cur_len, int cur_path[], int index, int shortest_path[])
{
    if (cur_city == dest)
    {
        shortest_path[N + 1] = cur_len;
        arrcpy(shortest_path, cur_path, N);
        shortest_path[N] = index;
        return index;
    }

    for (int city = 0; city < N; city++)
    {
        if (scorched[city] || index >= N)
            continue;

        int cur_road = map[cur_city][city];
        scorched[city] = 1;
        if (cur_road + cur_len < shortest_path[N + 1])
        {
            cur_path[index] = city;
            step_shortest(map, city, dest, scorched, cur_road + cur_len, cur_path, index + 1, shortest_path);
        }
        scorched[city] = 0;
    }
    return index;
}

int read_map(int map[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (scanf("%d", &map[i][j]) < 1)
                return -1;
        }
    }

    return 0;
}

void arrcpy(int dest[], int source[], int size)
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = source[i];
    }
}

void print_shortest_path(int *sol, int n)
{
    printf("The shortest path is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", sol[i]);
    }
}