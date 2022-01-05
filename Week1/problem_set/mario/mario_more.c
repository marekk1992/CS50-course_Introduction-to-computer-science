#include <stdio.h>
#include <cs50.h>

int main(void)

{
    //Promt user for height
    int x;

    do
    {
        x = get_int("Height: ");
    }
    while (x < 1 || x > 8);

    //Print pyramid on the left
    for (int y = 1; y <= x; y++)
    {
        for (int i = x; i > y; i--)
        {
            printf(" ");
        }
        for (int j = 0; j < y; j++)
        {
            printf("#");
        }
        //Make a gap between pyramids
        {
            printf("  ");
        }
        //Print pyramid on the right
        for (int k = 0; k < y; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
