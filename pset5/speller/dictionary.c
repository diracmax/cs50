// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
long dictionary_words_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_number = hash(word);

    for (node *tmp = table[hash_number]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    if (word != NULL)
    {
        return (tolower(word[0]) - 'a') % 26;
    }
    else
    {
        return 0;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }


    char store_characters[LENGTH + 1];

    //store characters
    while (fscanf(file, "%s", store_characters) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        int hash_number = hash(store_characters);
        strcpy(n->word, store_characters);

        n->next = table[hash_number];
        table[hash_number] = n;

        dictionary_words_count++;
    }

    fclose(file);


    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_words_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {

        node *n = table[i];
        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }
        if (i == N - 1 && n == NULL)
        {
            return true;
        }
    }
    return false;

}
