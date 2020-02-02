#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) == 0);

    // start with float values as they will be divided and returns float value w/o trauncating the decimals
    float letterCounter = 0, wordCounter = 1, sentenceCounter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Count the number of letters using isalpha (function that counts for letter, boolean)
        if (isalpha(text[i]))
        {
            letterCounter++;
        }
        // Then counts the number of words by counting (num of whitespace + 1), assume no whitespace at end of statement
        else if (isspace(text[i]))
        {
            wordCounter++;
        }
        // Then checks for num of sentence by counting specific punctuations
        else if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentenceCounter++;
        }
    }
    // calculate Coleman-Liau index and give grade
    int score = round((0.0588 * ((letterCounter * 100) / wordCounter))  - (0.296 * ((sentenceCounter * 100) / wordCounter)) - 15.8);
    if (score < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (score >= 16)
    {

        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", score);
    }
}
