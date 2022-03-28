import csv
import sys
import string


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Download CSVfile
    database = []

    # Make dictionary for everyone DNA information
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    database_key = []
    for i in database[0]:
        database_key.append(i)

    database_length = len(database)

    # Change string to int respectively
    str_kinds = len(database_key) - 1
    for row in range(database_length):
        for i in range(str_kinds):
            database[row][database_key[i + 1]] = int(database[row][database_key[i + 1]])

    # Download DNAtext
    dna = []

    with open(sys.argv[2]) as f:
        dna = f.read()

    # Make array for STRs of given DNAdata
    str_count = []

    for i in range(str_kinds):
        str_count.append(str_max_count(dna, database_key[i + 1]))

    # Match data against database
    no_match_count = 0
    for i in range(database_length):
        count = 0
        for j in range(str_kinds):
            if database[i][database_key[j + 1]] == str_count[j]:
                count += 1
        if count == str_kinds:
            print(database[i]["name"])
        else:
            no_match_count += 1

    if no_match_count == database_length:
        print("No match")


def str_max_count(DNA, STR):
    max_count = 0
    str_length = len(STR)
    dna_length = len(DNA)
    i = 0
    while i <= dna_length - str_length:
        if DNA[i:i + str_length] != STR:
            i += 1
            continue
        count = 0
        while DNA[i:i + str_length] == STR:
            count += 1
            i += str_length
            if i > dna_length - str_length:
                break
        if count >= max_count:
            max_count = count

    return max_count


if __name__ == "__main__":
    main()