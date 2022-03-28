#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string);
int count_words(string);
int count_sentences(string);

int main(void)
{
    string text = get_string("Text ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    double mean_letters = (double) letters / words * 100;
    double mean_sentences = (double) sentences / words * 100;
    double coleman_liau_index = 0.0588 * mean_letters - 0.296 * mean_sentences - 15.8;
    int index = round(coleman_liau_index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    //add last word
    words++;

    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.')
        {
            sentences++;
        }
        else if (text[i] == '?')
        {
            sentences++;
        }
        else if (text[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;

}