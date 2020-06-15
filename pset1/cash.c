// Assuming you spend a dollar on a product that cost less,
// return smallest amount of change you are due.
// Create input that asks how much change is owed,
// then calculate how much change back you get.


#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Create function to ask user for a total amount of change they are due
int changeTotal () {
    int changeTotal;
    do {
      changeTotal = get_int("Enter amount of change you are owed (1-99): ");
    } while(changeTotal < 1 || changeTotal > 100);

      return changeTotal;
}

// Create function that returns the least amount of coins the user is owed
// Use floor division and modulus operator
int main() {
    int n = changeTotal();
    int a;
    int b;
    int c;
    int d;
    double numQuarters = 0;
    double numDimes = 0;
    double numNickels = 0;

    numQuarters = floor(n / 25);
    printf("%f quarters\n", numQuarters);

    b = n % 25;
    numDimes = floor(b / 10);
    printf("%f dimes\n", numDimes);

    c = b % 10;
    numNickels = floor(c / 5);
    printf("%f nickels\n", numNickels);

    d = c % 5;
    printf("%i pennies\n", d);
}
