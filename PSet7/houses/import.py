from sys import argv, exit
import csv
from cs50 import SQL

def main():
    check_arg()
    read_file()


# accept name of csv as command line arguement
def check_arg():
    if len(argv) != 2:
        print("Usage: python import.py characters.csv")
        exit(1)

    elif 'csv' not in argv[1][-3:]:
        print('Usage: python import.py characters.csv')
        exit(1)


# Read files and append rows in db
def read_file():

    # Open db and table
    db = SQL("sqlite:///students.db")

    with open(argv[1], "r") as csv_file:
        file = csv.DictReader(csv_file)

        # read each entry and slot into db
        for row in file:
            name_lst = row['name'].split()

            first = name_lst[0]

            if len(name_lst) == 2:
                middle = None
                last = name_lst[1]
            elif len(name_lst) == 3:
                middle = name_lst[1]
                last = name_lst[2]

            house = row['house']
            birth = int(row['birth'])

            # insert into db
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                first, middle, last, house, birth)


# Run code
main()
