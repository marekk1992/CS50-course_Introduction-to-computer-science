#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

//Prototypes
int compute_score(string word);
void determine_winner(int player1_score, int player2_score);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Compute score for both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Determine the winner and print results
    determine_winner(score1, score2);
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int sum = 0;
    int j = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))
        {
            if (islower(word[i]))
            {
                word[i] = word[i] - 32;
            }
            //Assign points according to letter
            while (word[i] != letters[j])
            {
                j++;
            }
            sum = sum + POINTS[j];
            j = 0;
        }
    }
    return sum;
}

void determine_winner(int player1_score, int player2_score)
{
    if (player1_score > player2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player1_score < player2_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
