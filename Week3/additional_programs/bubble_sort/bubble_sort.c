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

    //Sort numbers in ascending order using bubble sort
    int swap_counter = -1;
    int sorted_element = 0;
    do
    {
        swap_counter = 0;
        int i = 0;
        for (int j = i + 1; j < (number_of_elements - sorted_element); i++, j++)
        {
            if (numbers[i] > numbers[j])
            {
                int temporary = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temporary;
                swap_counter++;
            }
        }
        sorted_element++;
    }
    while (swap_counter != 0);

    //Print sorted array of numbers
    for (int i = 0; i < number_of_elements; i++)
    {
        printf("%i ", numbers[i]);
    }
}