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

    with open(argv[1]) as csv_file:
        csv_reader = csv.DictReader(csv_file)

        # doing queries each student
        for student in csv_reader:
            raw_name = student['name']
            house = student['house']
            birth = student['birth']

            name = raw_name.split(" ")

            # object (dict) to make logic easier
            formatted_name = {
                'first': name[0],
                'middle': None if len(name) == 2 else name[1],
                'last': name[len(name) - 1]
            }

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);"
                        , formatted_name['first'], formatted_name['middle'], formatted_name['last'], house, birth)


main()

