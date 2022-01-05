#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number_of_elements = get_int("Number of elements: ");
    int numbers[number_of_elements];

    for (int i = 0; i < number_of_elements; i++)
    {
        numbers[i] = get_int("Number: ");
    }

    //Sort array in descending order using selection sort
    for (int j = 0; j < number_of_elements; j++)
    {
        int index_of_biggest = j;
        for (int i = j; i < number_of_elements; i++)
        {
            if (numbers[index_of_biggest] < numbers[i])
            {
                index_of_biggest = i;
            }
        }
        int temporary = numbers[index_of_biggest];
        numbers[index_of_biggest] = numbers[j];
        numbers[j] = temporary;
    }

    //Print sorted array
    for (int n = 0; n < number_of_elements; n++)
    {
        printf("%i ", numbers[n]);
    }
}
