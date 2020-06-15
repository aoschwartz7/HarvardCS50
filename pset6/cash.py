from cs50 import get_float


# Create function that uses floor division and modulus operator to calculate exact change
def leastChange():

    change = get_float("Change owed: ")

    quarters = change // 0.25
    change = change % 0.25

    dimes = change // 0.10
    change = change % 0.10

    nickles = change // 0.05
    change = change % 0.05

    pennies = change // 0.01
    change = change % 0.01

    print(int(quarters+dimes+nickles+pennies))

if __name__ == '__main__':
    leastChange()
