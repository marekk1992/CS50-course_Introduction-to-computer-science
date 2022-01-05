#include <cs50.h>
#include <stdio.h>

int main(void)

{
    // TODO: Prompt for start size
    int x;

    do
    {
        x = get_int("Start size: ");
    }
    while (x < 9);

    // TODO: Prompt for end size
    int y;

    do
    {
        y = get_int("End size: ");
    }
    while (y < x);

    // TODO: Calculate number of years until we reach threshold
    int i;
    int n;
    n = 0;

    if (x == y)
    {
        n = 0;
    }
    else
        do
        {
            i = x + (x / 3) - (x / 4);
            x = +i;
            n++;
        }
        while (x < y);

    // TODO: Print number of years
    {
        printf("Years: %i\n", n);
    }
}
