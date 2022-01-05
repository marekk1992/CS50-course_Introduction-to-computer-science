#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int count_reading_index(int letters, int words, int sentences);
void print_reading_grade(int index);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int reading_index = count_reading_index(letters, words, sentences);
    print_reading_grade(reading_index);
}

int count_letters(string text)
{
    int counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            counter++;
        }
    }
    return counter;
}

int count_words(string text)
{
    int counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ' || (text[i] == '.' && text[i + 1] != ' ') || (text[i] == '!' && text[i + 1] != ' ') || (text[i] == '?'
                && text[i + 1] != ' '))
        {
            counter++;
        }
    }
    return counter;
}

int count_sentences(string text)
{
    int counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}

int count_reading_index(int letters, int words, int sentences)
{
    float letters_average = (float) letters * 100 / (float) words;
    float sentences_average = (float) sentences * 100 / (float) words;
    float index = 0.0588 * letters_average - 0.296 * sentences_average - 15.8;
    index = round(index);
    return index;
}

void print_reading_grade(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
