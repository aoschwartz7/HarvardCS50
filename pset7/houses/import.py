import sys
import cs50
import csv


# Goal: import CSV data containing Hogwarts students info to students.db

# Check usage
if len(sys.argv) != 2:
    print("Usage: import.py [characters.csv]")
    sys.exit()

# Open db file we want to write to
open("students.db", "w")
db = cs50.SQL("sqlite:///students.db")

# Create tables
db.execute("CREATE TABLE students (first_name TEXT, middle_name TEXT, last_name TEXT, house text, year NUMERIC)")

# Open CSV in readmode
with open(sys.argv[1], 'r') as csvFile:
    reader = csv.DictReader(csvFile)

    # Iterate over CSV file
    for row in reader:
        if row['name']:
            splitName = row['name'].split()

            # Check for middle name
            if len(splitName) == 2:
                first_name = splitName[0]
                middle_name = "NULL"
                last_name = splitName[1]

            else:
                first_name = splitName[0]
                middle_name = splitName[1]
                last_name = splitName[2]

            # Include house and year
            house = row['house']
            year = int(row['birth'])

            # Insert values into table
            db.execute("INSERT INTO students (first_name, middle_name, last_name, house, year) VALUES (?, ?, ?, ?, ?)",
            first_name, middle_name, last_name, house, year)
