#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    int cents = round(dollars * 100);

    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    int coins = 0;

    if (cents >= quarter)
    {
        int quarter_count = cents / quarter;
        coins += quarter_count;
        cents -= quarter * quarter_count;
    }

    if (cents >= dime)
    {
        int dime_count = cents / dime;
        coins += dime_count;
        cents -= dime * dime_count;
    }

    if (cents >= nickel)
    {
        int nickel_count = cents / nickel;
        coins += nickel_count;
        cents -= nickel * nickel_count;
    }

    if (cents >= penny)
    {
        int penny_count = cents / penny;
        coins += penny_count;
        cents -= penny * penny_count;
    }

    printf("%i", coins);

}