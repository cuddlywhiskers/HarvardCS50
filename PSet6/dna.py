from sys import argv, exit
import csv
from cs50 import get_string


# Compile functions
def main():
    check_arg()
    person = read_file()
    print(person)


# Check command-line arguments and open file
def check_arg():
    if len(argv) != 3:
        print('Usage: python dna.py data.csv sequence.txt')
        exit(1)

    elif 'csv' not in argv[1][-3:] and 'txt' not in argv[2][-3:]:
        print('Usage: python dna.py data.csv sequence.txt')
        exit(1)


def read_file():
    # Read text file
    txt = open(argv[2], "r")
    sequence = txt.read()

    # Open csv file
    with open(argv[1], "r") as csv_file:
        file = csv.DictReader(csv_file)
        header = file.fieldnames
        dna_lst = header[1:]

        # count dna sequence
        d = dna_counter(sequence, dna_lst)

        # compare dna sequence with csv
        person = compare(file, d, dna_lst)

    return person


# count nucleotide bases in sequence based
def dna_counter(sequence, dna_lst):
    d = {}

    for dna in dna_lst:
        dna_l = len(dna)
        d[dna] = 0

        for start in range(len(sequence)):
            counter = 0
            end = dna_l + start

            # loop the subsequent string to check for repeats if first necleotide base is found
            while dna == sequence[start:end]:
                counter += 1
                start = start + dna_l
                end = end + dna_l

            if counter >= d[dna]:
                d[dna] = counter

    return d


# Compare with dictionary of neclotide counts with those in csv
def compare(file, d, dna_lst):

    person = 'No match'

    for f in file:
        for dna in dna_lst:
            f[dna] = int(f[dna])

        if d.items() <= f.items():
            person = f['name']

    return person


main()
