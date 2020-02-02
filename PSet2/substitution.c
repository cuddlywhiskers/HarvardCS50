#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Key Validity Check
    // Condition 1- there must be 2 arguments at command line
    if (argc != 2)
    {
        printf("./substitution key");
        return 1;
    }
    // Condition 2 - 26 characters in key
    int n = strlen(argv[1]);
    if (n != 26)
    {
        printf("Incorrect Number of Chars: Key must contain 26 characters.\n");
        return 1;
    }
    // Condition 3 - Check each character for alpbaets only
    for (int i = 0; i < n; i++)
    {
        int character = toupper(argv[1][i]);
        if (character < 65 || character > 90)
        {
            printf("Non Alphabets Found: Key must contain alphabetical characters only.\n");
            return 1;
        }
        else
        {
            // Condition 4 - Check for Duplicated Chracters by creating a 2nd loop that runs each character with loop 1.
            int charCounter = 0;
            for (int j = 0; j < n; j++)
            {
                if (toupper(argv[1][i]) == toupper(argv[1][j]))
                {
                    charCounter++;
                }
            }
            if (charCounter > 1)
            {
                printf("Duplicates Found: Key must contain 26 unique characters.\n");
                return 1;
            }
        }
    }

    // Encryption
    // Variables
    string key = argv[1], text = get_string("plaintext: ");
    int textLength = strlen(text);

    printf("ciphertext:");
    // Key characters and input characters must share common base values
    for (int k = 0; k < textLength; k++)
    {
        if (isalpha(text[k]) && isupper(text[k]))  //if alphabet and upper case, normalise to 0
        {
            for (int i = 0; i < n; i++)
            {
                int numeric = (int) text[k] - 65;
                if (numeric == i)   //compare position of alphbet in plain text with key
                {
                    printf("%c", toupper(key[i]));
                }
            }
        }
        else if (isalpha(text[k]) && islower(text[k]))
        {
            for (int i = 0; i < n; i++)
            {
                int numeric = (int) text[k] - 97;
                if (numeric == i)       //compare position of alphbet in plain text with key
                {
                    printf("%c", tolower(key[i]));
                }
            }
        }
        else
        {
            // if its not an upper or lower character, return the non-alpha character
            printf("%c", text[k]);
        }
    }
    printf("\n");
    return 0;
}
