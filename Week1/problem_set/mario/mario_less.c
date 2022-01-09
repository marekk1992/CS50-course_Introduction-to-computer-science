#include <stdio.h>
#include <cs50.h>

int main(void)

{
    // TODO Promt for pyramid height
    int x;

    do
    {
        x = get_int("Height: ");
    }
    while (x < 1 || x > 8);

    // TODO Print required amount of spaces on row depending on pyramid height
    for (int y = 1; y <= x; y++)
    {
        for (int i = x; i > y; i--)
        {
            printf(" ");
        }

        // TODO Print required amount of hashes on each row depending on number of spaces
        for (int j = 0; j < y; j++)
        {
            printf("#");
        }
        // Start new line
        printf("\n");
    }
}
