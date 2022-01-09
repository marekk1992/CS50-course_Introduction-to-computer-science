#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char uppercase_letter[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char lowercase_letter[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

//Prototypes

string encrypt_received_string(char uppercase_letter[], char lowercase_letter[], string plaintext, int key);
void print_ciphertext(string plaintext, string ciphertext);

int main(int number_of_arguments, string argument[])
{
    if (number_of_arguments != 2)
    {
        printf("Usage: ./caesar\n");
        return 1;
    }

    // Check whether argument consist only of digits
    for (int i = 0; i < strlen(argument[1]); i++)
    {
        if (argument[1][i] < '0' || argument[1][i] > '9')
        {
            printf("Usage: ./caesar\n");
            return 1;
        }
    }

    // Convert string to integer
    int key = atoi(argument[1]);

    string plaintext = get_string("plaintext: ");
    string ciphertext = encrypt_received_string(uppercase_letter, lowercase_letter, plaintext, key);
    print_ciphertext(plaintext, ciphertext);
    return 0;
}

string encrypt_received_string(char upper_case_letters[], char lower_case_letters[], string plaintext, int key)
{
    char encrypted_text[strlen(plaintext)];
    int j = 0;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            while (plaintext[i] != lower_case_letters[j])
            {
                j++;
            }
            encrypted_text[i] = lower_case_letters[(j + key) % 26];
            j = 0;
        }
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            while (plaintext[i] != upper_case_letters[j])
            {
                j++;
            }
            encrypted_text[i] = upper_case_letters[(j + key) % 26];
            j = 0;
        }
        else
        {
            encrypted_text[i] = plaintext[i];
        }
    }
    string ciphertext = encrypted_text;
    return ciphertext;
}

void print_ciphertext(string plaintext, string ciphertext)
{
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}
