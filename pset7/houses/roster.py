import sys
import cs50

# Write a program that prints a list of students for a given house in alphabetical order.


# Check usage
if len(sys.argv) != 2:
    print("Usage: roster.py [house]")
    exit()

# Open db we want to read from
open("students.db", "r")
db = cs50.SQL("sqlite:///students.db")

houseName = sys.argv[1].capitalize()

if houseName not in ["Slytherin", "Gryffindor", "Hufflepuff", "Ravenclaw"]:
    print("Usage: Housename error")
    exit()

# Run SQL query and return a list of all students belonging to house
for row in db.execute(
    """ SELECT * FROM students
    WHERE house = "{}"
    ORDER BY last_name
    """.format(houseName)git ):

    # Include middle name if student has one
    if row['middle_name'] != "NULL":
        print("{} {} {}, born {}".format(row['first_name'], row['middle_name'], row['last_name'], row['year']))

    # Else just use first, last name
    else:
        print("{} {}, born {}".format(row['first_name'], row['last_name'], row['year']))
