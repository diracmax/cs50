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
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int count = 0;
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!(isupper(argv[1][i]) || islower(argv[1][i])))
        {
            count++;
        }
    }
    if (count != 0)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }
            }
        }
    }

    // If the key is valid, you can receive the plaintext.
    string plaintext = get_string("plaintext:");

    int plaintext_length = strlen(plaintext);
    // prepare ciphertext
    char ciphertext[plaintext_length + 1];
    ciphertext[plaintext_length] = 0;
    // encrypting
    for (int i = 0; i < plaintext_length; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = toupper(argv[1][plaintext[i] - 'A']);
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = tolower(argv[1][plaintext[i] - 'a']);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}