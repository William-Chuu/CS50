from cs50 import SQL
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

    if len(argv) != 2:
        print("Usage: python roster.py HOUSE")
        exit(1)

    # returns dict with each column name as the key
    rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last", argv[1])

    # print out each row by calling the dict created from the query db.execute
    for row in rows:
        print(row['first'] + " " + (row['middle'] + " " if row['middle'] else "") + row['last'] + ", born", row['birth'])


main()