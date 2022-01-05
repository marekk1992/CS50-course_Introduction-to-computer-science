#include <stdio.h>
#include <cs50.h>

int main(void)

{
    // Get a number from user
    long number = get_long("Number: ");

    // Check if number is proper lenght
    if (number < 1000000000000 || number > 10000000000000000 || (number / 10000000000000 > 0 && number / 10000000000000 < 10))
    {
        printf("INVALID\n");
    }
    else
    {
        // Evaluate how many digits number is
        int digit_counter = 0;

        if ((number / 1000000000000) > 0 && (number / 1000000000000) < 10)
        {
            digit_counter = 13;
        }
        else if ((number / 100000000000000) > 0 && (number / 100000000000000) < 10)
        {
            digit_counter = 15;
        }
        else if ((number / 1000000000000000) > 0 && (number / 1000000000000000) < 10)
        {
            digit_counter = 16;
        }

        int sum = 0;
        int digit;
        long divider = 1;

        for (int i = 1; i <= digit_counter; i++)
        {
            // Find out odd digits of the given number
            if (i % 2 != 0)
            {
                digit = (number / divider) % 10;
            }
            else
            {
                // Find out even digits of the given number ant multiply by 2
                digit = ((number / divider) % 10) * 2;
                if (digit >= 10)
                {
                    digit = digit / 10 + digit % 10;
                }
            }
            divider = divider * 10;
            // Sum all digits
            sum = sum + digit;
        }

        // Evaluate all digits checksum
        if (sum % 10 != 0)
        {
            printf("INVALID\n");
        }
        else
        {
            // Check card numbers starting digits and print AMEX, VISA, MASTERCARD or INVALID according to it
            if (number / 10000000000000 == 34 || number / 10000000000000 == 37)
            {
                printf("AMEX\n");
            }
            else if (number / 1000000000000 == 4 || number / 1000000000000000 == 4)
            {
                printf("VISA\n");
            }
            else if (number / 100000000000000 == 51 || number / 100000000000000 == 52 || number / 100000000000000 == 53
                     || number / 100000000000000 == 54 || number / 100000000000000 == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
}
