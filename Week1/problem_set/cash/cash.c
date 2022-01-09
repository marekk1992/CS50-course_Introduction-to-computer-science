#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{
    // Get change from user
    float dollars;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    // Convert dollars to cents
    int cents = round(dollars * 100);

    // Calculate minimum number of coins required
    int amount_of_coins = cents / 25;
    cents = cents % 25;
    amount_of_coins = amount_of_coins + cents / 10;
    cents = cents % 10;
    amount_of_coins = amount_of_coins + cents / 5;
    cents = cents % 5;
    amount_of_coins = amount_of_coins + cents;

    // Print the result
    printf("%i\n", amount_of_coins);
}
