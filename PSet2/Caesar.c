#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// int argc : number of arguments passed for ./caesar a b c (4, inclusive of ./caesar)
// string argv[]: gets the arguments depending on position, eg. argv[0] == ./caesar
// return num, where num != 0, end the loop and program.

int main(int argc, string argv[])
{
    // Check for number of arguments passed, exit programme if argc != 2.
    if (argc == 2)
    {
        // loop through individual characters in key, and check for non-digits, exit program if non-digits.
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if ((argv[1][i]) < 48 || argv[1][i] > 57)
            {
                printf("Usage: ./caesar key");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    // variables and prompt user for text
    int key = atoi(argv[1]);
    string text = get_string("plaintext: ");

    // interate over the plain text and shift the letters by key
    printf("ciphertext:");
    for (int k = 0, textLength = strlen(text); k < textLength; k++)
    {
        if (isupper(text[k]))
        {
            // converts character to numeric ASCII, performs formula
            int numeric = (int) text[k] - 65;
            char c = ((numeric + key) % 26) + 65;
            printf("%c", c);
        }
        else if (islower(text[k]))
        {
            // converts character to numeric ASCII, performs formula
            int numeric = (int) text[k] - 97;
            char c = ((numeric + key) % 26) + 97;
            printf("%c", c);
        }
        else
        {
            // if its not an upper/lowercase alphabet, return character
            printf("%c", text[k]);
        }
    }
    printf("\n");
}
