# Let the user decide just how tall Mario's pyramids should be by first
# prompting them for a positive integer between 1 and 8, inclusive.
# Here’s how the program might work if the user inputs 8 when prompted:
#  $ python mario.py
#  $ Height: 8
#         #  #
#        ##  ##
#       ###  ###
#      ####  ####
#     #####  #####
#    ######  ######
#   #######  #######
#  ########  ########

# Prompt user for height between 1-8 and store that as a variable
def answer():
    while True:
        try:
            n = int(input("Height: (1-8) "))
            if 1 <= n < 9:
                break
            else:
                print('Out of range. Try again')
        except:
          print ("That's not a number")
    return n

# Create function for adding spaces incrementing as range increases
def spaces(x):
    for a in range(x):
        print(" ", end = "")
# Create function for adding hashes incrementing as range increases
def hashes(n):
    for a in range(n):
        print("#", end = "")
# Create main function that takes height from answer() and
# passes it through spaces() and hashes().
# Decrement spaces, increment hashes
def makePyramid():
    n = answer()
    for a in range(1, n+1, 1):
        spaces(n-a)
        hashes(a)
        spaces(2)
        hashes(a)
        print("")

if __name__ == '__main__':
    makePyramid()
