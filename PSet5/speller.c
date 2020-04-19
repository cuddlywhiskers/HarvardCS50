// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
const unsigned int N = 1;

// Hash table (pointers to head of link list)
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash the word to get an index and access the array
    int n = hash(word);

    // Create cursor and point at first element
    node *cursor = table[n];

    // Loop through the linked list at index of hash table
    while (cursor != NULL)
    {
        if ((strcasecmp(word, cursor->word)) == 0)
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
// Implemented djb2 hashtable credits to: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *str)
{
    unsigned int hash = 5381;
    int c;

    // Iterate through the characters of string
    while ((c = *str++))
    {
        // case sensitive
        c = tolower(c);

        // Calculate (hash * 33) + c
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    
    // return something that is not > N
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
int counter = 0;
bool load(const char *dictionary)
{
    // Open dictionary and read dictionary, check for NULL
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("File cannot be opened.\n");
        return false;
    }

    // Read each word in the dictionary until the end of dictionary
    char dictWord[LENGTH + 1];
    while (fscanf(file, "%s", dictWord) != EOF)
    {
        // Allocate memory for a new node for each new word.
        node *tmp = malloc(sizeof(node));

        // Check whether malloc has enu memory to store node
        if (tmp == NULL)
        {
            return false;
        }

        // Store the word into a tmp node.
        strcpy(tmp->word, dictWord);

        // get hash index
        int index = hash(tmp->word);

        // tmp pointer -> hashtable, hashtable -> new pointer
        tmp->next = table[index];
        table[index] = tmp;
        counter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // IF not loaded, gives 0 else number of words
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int n = 0;

    // iterate through hash table
    while (n < N)
    {
        node *cursor = table[n];
        node *tmp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        n++;
    }
    return true;
}
