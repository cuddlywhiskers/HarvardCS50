#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int row;
    do
    {
        row = get_int("Rows: ");
    }
    while (row <= 0 || row >= 9);
//  for i in range(1,n): pythonic way
    for (int i = 1; i <= row; i++)
    {
        //  print whitespace until n -1 
        for (int leftSpace = 1; leftSpace <= (row - i); leftSpace++)
        {
            printf(" ");
        }
        //  print hash where hash = row num
        for (int leftHash = 1; leftHash <= i; leftHash++)
        {
            printf("#");
        }
        //  print two whitespaces 
        for (int width = 1; width <= 2; width++)
        {
            printf(" ");
        }
        //  print right hash where right hash = row num
        for (int rightHash = 1; rightHash <= i; rightHash++)
        {
            printf("#");
        }
        printf("\n");
    }
}
