// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Number of words in hash table
int number_of_words_in_hash_table = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_code = hash(word);
    node *cursor = table[hash_code];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 65;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    
    char scanned_word[LENGTH + 1];
    int index_of_hash_table;
    while (fscanf(file, "%s", scanned_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, scanned_word);
        number_of_words_in_hash_table++;
        index_of_hash_table = hash(n->word);
        if (table[index_of_hash_table] != NULL)
        {
            n->next = table[index_of_hash_table];
            table[index_of_hash_table] = n;
        }
        else
        {
            table[index_of_hash_table] = n;
            table[index_of_hash_table]->next = NULL;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return number_of_words_in_hash_table;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *temporary = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temporary);
            temporary = cursor;
        }
    }
    return true;
}
