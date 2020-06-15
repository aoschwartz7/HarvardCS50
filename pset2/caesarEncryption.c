// GOAL: allow user to enter an integer value that will serve as the encryption
// key to convert plaintext to ciphertext. For example, a key of 1 would turn
// "hello" to "ifmmp", since h equals 104 according to ASCII and we are adding a
//  value of 1 to it, etc.

// Note to self -- remember to compile with -lcs50 to get around linker command errors

// pseudocode:
// 1. check that program was run with one command-line argument
// 2. iterate over provided argument (which is the key) to make sure all characters are digits
// 3. convert argument from string to int
// 4. prompt user for plaintext
// 5. add plaintext to array
// 6. convert each element in array to new element by adding key to element
// 7. print new ciphertext

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//  Create global constant for whitespace
char whitespace = ' ';

int main(int argc, string argv[])
{
  // Check that program was run with just one command-line argument
  if (argc != 2)
  {
      printf("Usage: ./caesar key (digit)\n");
      return 1;
  }
  // Check if command-line argument consists of digits as key
  int key = atoi(argv[1]);
  if (key == 0)
  {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  // Ask user for text
  string text = get_string("Provide message to be encrypted: \n");

  // Find size of text for creating plainText array for encryption
  int n = strlen(text);
  int plainText[n];

  // Check if string is purely letters (upper or lowercase is fine)
  for (int i = 0; i < n; i++)
  {
    // Cast char in string as int
    int letter = text[i];
    // Check if letter is upercase
    if (letter >= 'A' && letter <= 'Z')
    {
      plainText[i] = letter;
    }
    // Check if letter is lowercase
    else if (letter >= 'a' && letter <= 'z')
    {
      plainText[i] = letter;
    }
    // Check for whitespace
    else if (letter == whitespace)
    {
      plainText[i] = whitespace;
    }
    else
    {
      printf("Enter letters only \n");
    }
  }
  // Encrypt message using key
  int encryptedText[n];
  for (int i = 0; i < n; i++)
  {
    // If sum of key + letter exceeds alphabet range, add difference to 'a' or 'A'
    int sum = plainText[i] + key;
    // First check for whitespace
    if (sum == whitespace + key)
    {
      encryptedText[i] = whitespace;
    }
    else if (sum > 'Z' && sum < 'a')
    {
      encryptedText[i] = 'A' + sum - 'Z' - 1;
    }
    else if (sum > 'z')
    {
      encryptedText[i] = 'a' + sum - 'z' - 1;
    }
    else
    {
      encryptedText[i] = plainText[i] + key;
    }
    printf("%c", encryptedText[i]);
  }
  printf("\n");
}
