#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Prototypes
bool is_correct_usage(int argument);
bool is_valid_key(string key);
string encrypt_received_string(string plaintext, string key);

int main(int command_line_arguments, string argument[])
{
    if (!is_correct_usage(command_line_arguments))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (!is_valid_key(argument[1]))
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    string ciphertext = encrypt_received_string(plaintext, argument[1]);
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool is_correct_usage(int argument)
{
    return (argument == 2);
}

bool is_valid_key(string key)
{
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only alphabetic characters.\n");
            return false;
        }
    }

    for (int i = 0; i < strlen(key) - 1; i++)
    {
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }
    }
    return true;
}

string encrypt_received_string(string plaintext, string key)
{
    char encrypted_text[strlen(plaintext) + 1];
    encrypted_text[strlen(plaintext)] = '\0';
    int j = 0;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            while (plaintext[i] != (65 + j))
            {
                j++;
            }
            encrypted_text[i] = toupper(key[j]);
            j = 0;
        }
        else if (islower(plaintext[i]))
        {
            while (plaintext[i] != (97 + j))
            {
                j++;
            }
            encrypted_text[i] = tolower(key[j]);
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
