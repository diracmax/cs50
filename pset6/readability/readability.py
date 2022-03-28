from cs50 import get_string


def count_letters(text):
    letters = 0
    n = len(text)
    for i in range(n):
        if text[i].isupper() or text[i].islower():
            letters += 1
    return letters


def count_words(text):
    words = 0
    n = len(text)
    for i in range(n):
        if text[i] == ' ':
            words += 1
    words += 1
    return words


def count_sentences(text):
    sentences = 0
    n = len(text)
    for i in range(n):
        if text[i] == '.' or text[i] == '?' or text[i] == '!':
            sentences += 1
    return sentences


text = get_string("Text: ")
letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)
mean_letters = letters / words * 100
mean_sentences = sentences / words * 100
coleman_liau_index = 0.0588 * mean_letters - 0.296 * mean_sentences - 15.8
index = round(coleman_liau_index)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")