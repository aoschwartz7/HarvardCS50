// Let the user decide just how tall Mario's pyramids should be by first
// prompting them for a positive integer between 1 and 8.
// Here’s how the program might work if the user inputs 8 when prompted:
//   $ ./mario
//   Height: 8
//          #  #
//         ##  ##
//        ###  ###
//       ####  ####
//      #####  #####
//     ######  ######
//    #######  #######
//   ########  ########

#include <cs50.h>
#include <stdio.h>

//prompt user for height between 1-8 and store that as a variable
int answer() {
  int i;
  do {
    i = get_int("Height(1-8): ");
  } while(i < 1 || i > 8);

    return i;
}

//create function for adding spaces incrementing as range increases
void spaces(int x) {
  for (int y = 0; y < x; y++)
  {
    printf(" ");
  }
}
//create function for adding hashes incrementing as range increases
void hashes(int x) {
  for (int y = 0; y < x; y++)
  {
    printf("#");
  }
}

//create main function that takes height from answer() and passes it through spaces() and hashes()
//decrement spaces, increment hashes
int main() {
  int n = answer();
  for (int y = 0; y < n+1; y++)
  {
    spaces(n-y);
    hashes(y);
    spaces(2);
    hashes(y);
    printf("\n");
  }
  return 0;
}
