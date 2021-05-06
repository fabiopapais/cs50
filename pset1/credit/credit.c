#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

long checkSum(long number);
int lengthHelper(long number);

int main(void)
{
    long number = get_long("Number: ");

    long lastDigit = checkSum(number);
    int length = lengthHelper(number);

    // printf("%i", length);

    if (lastDigit == 0)
    {
        long secondDigit = 0;
        long firstDigit = 0;
        int i = 1;
        long numberDigit = 0;
        while(number)
        {
            numberDigit = number % 10;
            number /= 10;

            if (i == length)
            {
                firstDigit = numberDigit;
            }
            else if (i == length - 1)
            {
                secondDigit = numberDigit;
            }
            i++;
        }
        // printf("first %li \n", firstDigit);
        // printf("second %li \n", secondDigit);

        if (length == 16)
        {
            // VISA
            if (firstDigit == 4)
            {
                printf("VISA\n");
            }
            // MASTERCARD
            else if ((firstDigit == 5 && secondDigit == 1) || (firstDigit == 5 && secondDigit == 2) ||
                (firstDigit == 5 && secondDigit == 3) || (firstDigit == 5 && secondDigit == 4) ||
                (firstDigit == 5 && secondDigit == 5))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 13)
        {
            // VISA
            if (firstDigit == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 15)
        {
            // AMEX
            if ((firstDigit == 3 && secondDigit == 4) || (firstDigit == 3 && secondDigit == 7))
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function responsable for making the sum part of the algorithm
long checkSum(long number)
{
    long digit = 0;

    long evens = 0;
    long odds = 0;

    int i = 0;

    long oddDigits = 0;
    long oddDigit = 0;

    long sumLastDigit = 0;

    while (number)
    {
        digit = number % 10;
        number /= 10;

        if (i % 2 == 0)
        {
            evens += digit;
        }
        else
        {
            oddDigits = digit * 2;
            if (oddDigits >= 10)
            {
                oddDigit = 0;
                while (oddDigits)
                {
                    oddDigit = oddDigits % 10;
                    oddDigits /= 10;

                    odds += oddDigit;
                }
            }
            else
            {
                odds += oddDigits;
            }
        }
        i++;
    }
    long sum = odds + evens;
    printf("%li and %li and %li", sum, odds, evens);
    sumLastDigit = sum % 10;

    return sumLastDigit;
}

// Simple function to get the length of an number (the quantity os digits)
int lengthHelper(long number)
{
    int counter = 0;
    while (number != 0)
    {
        number /= 10;
        counter++;
    }
    return counter;
}