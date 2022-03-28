#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // remove invalid key
    if (argc != 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!(isdigit(argv[1][i])))
        {
            printf("Usage: ./caesar key");
            return 1;
        }
    }

    int key = atoi(argv[1]);

    // If the key is valid, you can receive the plaintext.
    string plaintext = get_string("plaintext:");
    int plaintext_length = strlen(plaintext);
    char ciphertext[plaintext_length + 1];
    ciphertext[plaintext_length] = 0;

    // encrypting
    for (int i = 0; i < plaintext_length; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = ((plaintext[i] - 'A') + key) % 26 + 'A';
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = ((plaintext[i] - 'a') + key) % 26 + 'a';
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}