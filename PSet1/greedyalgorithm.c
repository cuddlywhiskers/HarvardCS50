#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0); 
    // convert change from dollars to cents    
    int coins = round(change * 100);
    int counter = 0;
    // if coins >= 25, add coins and deduct amount. creates infinite loop until condition == False
    while (coins >= 25)
    {
        counter++;
        coins = coins - 25;
    }
    // if coins >= 10, add coins and deduct amount      
    while (coins >= 10)
    {
        counter++;
        coins = coins - 10;
    }
    // if coins >= 5, add coins and deduct amount 
    while (coins >= 5)
    {
        counter++;
        coins = coins - 5;
    }
    // if coins >= 1, add coins and deduct amount 
    while (coins >= 1)
    {
        counter++;
        coins = coins - 1;
    }
    printf("%i\n", counter);
}
