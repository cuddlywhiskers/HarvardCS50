from sys import argv, exit
from cs50 import SQL
import csv


# compile codes
def main():
    check_arg()
    get_students()


# Check arg
def check_arg():
    # Check for number of arguments
    if len(argv) != 2:
        print("Usage: python roster.py name")
        exit(1)

    # Check whether name of house.is in current house list
    hse_lst = all_houses()
    if argv[1] not in hse_lst:
        print("Input correct house name.")
        exit(1)


# Checks for name of house in database
def all_houses():
    hse_lst = []

    db = SQL("sqlite:///students.db")
    house = db.execute("SELECT distinct(house) FROM students")
    for h in house:
        hse_lst.append(h['house'])

    return hse_lst


# Print students from the house
def get_students():
    db = SQL("sqlite:///students.db")

    rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house =? ORDER BY last, first", argv[1]);

    for row in rows:

        if row['middle'] == None:
            name = " ".join([row['first'], row['last']])
        else:
            name = " ".join([row['first'], row['middle'], row['last']])

        print(name + ", born " + str(row['birth']))


# Compile codes
main()
