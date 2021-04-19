#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define ITERATIONS 1000000000

double get_random() { return ((double)rand() / (double)RAND_MAX); } // return random value between 0 and 1

int main()
{

    double pi = 0;
    srand(time(NULL));

    for (int i = 0; i <= ITERATIONS; i++)
    {
        double rand = get_random();
        pi += sqrt(1 - rand * rand);
    }

    pi /= ITERATIONS;
    printf("%lf", pi * 4);
    return 0;
}