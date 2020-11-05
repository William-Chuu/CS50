from cs50 import SQL
import csv
from sys import argv


db = SQL("sqlite:///students.db")
# CREATE TABLE students (
#     id INTEGER PRIMARY KEY AUTOINCREMENT,
#     first VARCHAR(255),
#     middle VARCHAR(255),
#     last VARCHAR(255),
#     house VARCHAR(10),
#     birth INTEGER
# );


def main():
    # python import.py characters.csv
    if len(argv) != 2:
        print("Usage: python import.py characters.csv")
        exit(1)

    with open(argv[1]) as characters_csv:
        # name, house, birth
        csv_reader = csv.DictReader(characters_csv)
        for row in csv_reader:
            # splits name into a list where each word is a list item
            name = row['name'].split()
            if len(name) == 3:
                first = name[0]
                middle = name[1]
                last = name[2]
            elif len(name) == 2:
                first = name[0]
                middle = None
                last = name[1]
            house = row['house']
            birth = row['birth']

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)


main()