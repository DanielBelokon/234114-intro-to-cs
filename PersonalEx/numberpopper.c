#include <stdio.h>

int number = 0;

int generate_random();              // Generate a random number
void reduce(int index, int amount); // Reduce the number at the index
void erase(int index);              // erase the numbers to the right of the index (including)

int main()
{
    int players = 2;
    number = generate_random();

    printf("Enter the amount of players:\n");

    if (!scanf("%d", &players) && players > 0)
        printf("Defaulting to ");
    printf("%d players\n");

    int step = 0;

    int index, amount;

    while (!number)
    {
        printf("Player number %d - enter the index followed by the amount\n", (++step) % players);
        while (!scanf(" %d %d", &index, &amount))
        {
            printf("Try again...\n");
        }

        reduce(index, amount);
        printf("The number is: %d", number);
    }

    printf("Player %d LOST!", (step) % players);

    return 0;
}

int generate_random()
{
    srand();
    return rand();
}

void reduce(int index, int amount)
{
    int digit = 0;
    if (index == 1)
        digit = number % 10;

    if ((number / ((index - 1) * 10)) % 10 < amount)
        amount = digit;
    number -= amount * pow(10, (index - 1));
}

void erase(int index)
{
}

int pow(num, power)
{
    if (power == 0)
        return 0;

    for (int i = 0; i < power; i++)
    {
        num *= num;
    }
}