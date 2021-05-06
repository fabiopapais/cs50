// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000; // more buckets, faster (we dont really care with memory here)

// Global variable that represents the size of the dictionary
unsigned int dictionary_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *list = table[hash(word)];

    for (node *cursor = list; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 found on: https://stackoverflow.com/questions/14409466/simple-hash-functions
    unsigned int hash_address = 5381;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_address = ((hash_address << 5) + hash_address) + tolower(word[i]);
    }

    return hash_address % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char temp_word[LENGTH + 1];

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    while(fscanf(file, "%s", temp_word) != EOF)
    {
        unsigned int word_hash = hash(temp_word);
        node *temp_node = malloc(sizeof(node));
        if (temp_node == NULL)
        {
            return false;
        }

        strcpy(temp_node->word, temp_word); // It could be "(*n).word"

        temp_node->next = table[word_hash];
        table[word_hash] = temp_node;

        dictionary_size++;
    }

    if (ferror(file))
    {
        fclose(file);
        // dictionary_size = 0;
        return false;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *cursor = table[i]->next;
            free(table[i]);
            table[i] = cursor;
        }
    }
    return true;
}
