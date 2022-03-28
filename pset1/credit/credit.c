#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //receive number
    long number = get_long("Number: ");

    int odd_total = 0;
    int even_total_double = 0;

    //Luhn's Algorithm
    long n = number;
    int count = 0;
    int upper_two_digits;
    while (n > 0)
    {
        int digits = n % 10;
        if (count % 2 == 0)
        {
            odd_total += digits;
        }
        else
        {
            int j = 2 * digits;
            if (j >= 10)
            {
                int k = j % 10;
                j = (j - k) / 10;
                even_total_double += (j + k);
            }
            else
            {
                even_total_double += j;
            }
        }
        n = (n - digits) / 10;
        count++;
        //receive upper two digits
        if (n < 100 && n > 9)
        {
            upper_two_digits = n;
        }
    }

    //research what your credit number card is and whether it is valid or not
    int all = even_total_double + odd_total;

    if (all % 10 == 0)
    {
        switch (upper_two_digits)
        {
            case 34:
            case 37:
                //AMEX number digits are 15
                if (count == 15)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
                //VISA number digits are 13 or 16
                if (count == 13 || count == 16)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                //MASTERCARD number digits are 16
                if (count == 16)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            default:
                printf("INVALID\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }
}