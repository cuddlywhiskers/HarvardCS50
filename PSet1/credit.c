#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long number;
    number = get_long("Credit Card Number: ");
    
    // Get the last digit and every alternate digit and sum
    // lastDigitSeq: sequence of numbers starting from last digits 
    // secondLastSeq: sequence of numbers starting from second last digit
    long number1 = number;
    int lastDigitSeq = 0;
    while (number1 != 0)
    {
        int digit = (number1 % 10);
        lastDigitSeq = lastDigitSeq + digit;
        number1 = number1 / 100;
    }
    
    // Get the second last digit and every alternate digits, x2
    long number2 = (number / 10);
    int secondLastSeq = 0;
    while (number2 != 0)
    {
        int individualDigit = (number2 % 10) * 2;
        number2 = number2 / 100;
        
        // For each of these individual digits, perform %10 and the remainder for these indi digits.
        int sumIndividualDigit = 0;
        while (individualDigit != 0)
        {
            int remainder = (individualDigit % 10);
            sumIndividualDigit = sumIndividualDigit + remainder;
            individualDigit = individualDigit / 10;
        }
        secondLastSeq = secondLastSeq + sumIndividualDigit;
    }
    
    // Sum the digits and calculate the remainder for last digit upon %10. 
    int checksum = secondLastSeq + lastDigitSeq;

    // Get credit card number length   
    long number3 = number;
    int length = 2;
    while (number3 / 10 >= 10)
    {
        length++;
        number3 = number3 / 10;
    }    
    
    // Get starting digits to check card validity
    // Create conditions to check for cards, if found gives name of card else invalid.
    int firstDigit = number / pow(10, (length - 1)); 
    int firstTwoDigits = number / pow(10, (length - 2));
    
    if ((firstDigit == 4) && (checksum % 10 == 0) && (length == 13 || length == 16)) 
    {
        printf("VISA\n");   
    }
    
    else if ((firstTwoDigits == 34 || firstTwoDigits == 37) && (checksum % 10 == 0) && (length == 15)) 
    {
        printf("AMEX\n");
    }
    
    else if ((firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55) 
             && (checksum % 10 == 0) && (length == 16))
    {
        printf("MASTERCARD\n");
    }
    
    else
    {
        printf("INVALID\n");
    }
}
