#include <stdio.h>
#include <cs50.h>

//Prototype
int count_factorial(int number);

int main(void)
{
    int number = get_int("Enter number: ");
    int factorial = count_factorial(number);
    printf("%i\n", factorial);
}

int count_factorial(int number)
{
    //base case
    if (number == 1)
    {
        return number;
    }

    //recursive case
    return number*count_factorial(number - 1);
}

