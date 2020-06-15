from csv import reader, DictReader
import sys



# https://cs50.harvard.edu/x/2020/psets/6/dna/
# Given a DNA sequence, check to see if it matches individuals  for whom we have
# target STR information.

# - Open CSV file and text file containing DNA sequence and read contents to memory
# - Create dictionary containing target STR
# - For each STR, compute the longest consecutive repeats found in DNA
# - Compare STR counts against each row in CSV file

strTargets = {}     # Store STR targets globally
dna = []            # Store DNA sequence globally
individuals = []    # Store individuals' target STR information globally


# Create function that takes command-line arguments for files and then loads
# them to global variables above.
def loadFiles():

    # Check usage:
    if len(sys.argv) != 3:
        print("Usage: dna.py [DATABASE.csv] [SEQUENCE.txt]") # i.e. python3 dna.py databases/small.csv sequences/1.txt
        sys.exit()

    # Open CSV file containing individuals and their STR counts and read contents to memory
    with open(sys.argv[1], 'r') as individualsCSV:

        individualsReader = DictReader(individualsCSV)  # Read CSV

        global individuals
        for person in individualsReader: # Store CSV rows (people) as ordered dictionaries (tuples)
            individuals.append(person)      #     within individuals[]

        global strTargets
        strTargets = individualsReader.fieldnames[1:]   # Store CSV header (STR targets) as a list
        strTargets = dict.fromkeys(strTargets , 0)  # Convert list to dictionary

    # Open text file containing DNA sequence and read contents to memory
    with open(sys.argv[2], 'r') as dnaFile:
        dnaReader = reader(dnaFile)

        # Store DNA sequence as a string
        for row in dnaReader:
            global dna
            dna = row[0]

# Create function to find occurrence count of overlapping STR substrings.
# Start from left and search for substring; when found, increment counter and
# keep searching from next index position. If a consecutive STR is found, tally
# it and keep track of largest tally found in DNA sequence. Afterward, update
# strTargets{} with max tally for each STR target

def countSTR(strTargets, dna):

    for STR in strTargets:

        tempCount = 0   # Initialize STR counter
        tempMax = 0     # Initialize counter for max STR found
        l = len(STR)    # Determine STR length for indexing into DNA string below

        for i in range(len(dna)):

            if STR == dna[i:i+l]:  # Find STR occurrence in DNA sequence
                tempCount+=1    # Increment STR counter

                while STR == dna[i+l:(i+l)+l]:  # Check for consecutive repeat
                    tempCount+=1    # Increment if found
                    i+=l    # Increment indexer so it skips to next possible STR

                if tempCount > tempMax:
                    tempMax = tempCount

                tempCount = 0   # Reset STR count once repeats finish

        value = {STR: tempMax}
        strTargets.update(value)
    return strTargets

# Create function to compare target STR count in DNA to individuals and check
# for a match.

def compare(strTargets, individuals):

    completeMatch = len(strTargets)  # Represents an individual's complete STR match to DNA
    matchedPerson = None

    for person in individuals:
        partialMatch = 0
        for STR in strTargets:
            if strTargets[STR] == int(person[STR]):    # Check if person's STR count equals DNA's STR count
                partialMatch +=1
            if partialMatch == completeMatch:
                matchedPerson = person['name']
    if matchedPerson is not None:
        print(matchedPerson)
    else:
        print("No match")

if __name__ == '__main__':
    loadFiles()
    countSTR(strTargets, dna)
    compare(strTargets, individuals)
