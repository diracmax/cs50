#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int initial;
    int final;
    do
    {
        initial = get_int("Start size: ");
    }
    while (initial < 9);
    // TODO: Prompt for end size
    do
    {
        final = get_int("End size: ");
    }
    while (initial > final);

    // TODO: Calculate number of years until we reach threshold
    int year = 0;
    while (initial < final)
    {
        initial += initial / 3 - initial / 4;
        year++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", year);
}