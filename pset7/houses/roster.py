import sys
import csv
from cs50 import SQL

# Global variable that permit the SQL queries
db = SQL("sqlite:///students.db")


def main():
    argv = sys.argv
    argc = len(argv)

    # validation of arguments
    if argc != 2:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # his variable stores the user's input
    house = argv[1]

    selected_students = db.execute(
        "SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first ASC", house)

    # simple logic to display middle name or not
    for student in selected_students:
        middle = student['middle']
        if middle == None:
            print(f"{student['first']} {student['last']}, born {student['birth']}")
        else:
            print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")


main()
