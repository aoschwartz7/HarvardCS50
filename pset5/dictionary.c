#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 65536    // Total number of words in dictionary/large

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Declare dictionarySize to later measure number of words in file
int dictionarySize = 0;


// Hash table with the number of buckets being HASHTABLE_SIZE
node *hashTable[HASHTABLE_SIZE];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int len = strlen(word);
    char lword[len + 1];
    for (int i = 0; i < len; i++)
    {
        lword[i] = tolower(word[i]);
    }
    lword[len] = '\0';
    
    int bucket = hash(lword);
    node *cursor = hashTable[bucket];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, lword) != 0)
            cursor = cursor->next;
        else
            return true;
    }
    return false;
}

// Hashes word to a number
// Source for hash function: Github User yangrq1018
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % HASHTABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dictFile = fopen(dictionary, "r");

    if (!dictFile)
    {
        fprintf(stderr, "Cound not open %s.\n", dictionary);
        return false;
    }

    char buffer[LENGTH + 1];

    // Scan dictionary file and hash file contents
    while (fscanf(dictFile, "%s", buffer) != EOF)
    {
        // Create a temporary node
        node *temp = malloc(sizeof(node));

        strncpy(temp->word, buffer, sizeof(buffer));
        
        // Call hash function to get index of word
        int index = hash(buffer);
        
        // If the corresponding index in hash table is empty, assign it to the temp node
        if (hashTable[index] == NULL)
            hashTable[index] = temp;

        // Else append temp to the start of the linked list
        else
        {
        temp->next = hashTable[index];
        hashTable[index] = temp;
        }

    dictionarySize++;

    }

    fclose(dictFile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    printf("WORDS IN DICTIONARY: %i \n", dictionarySize);
    return true;
}

// Dismantle nodes in hash table
void destroy(node *head)
{
    if (head->next != NULL)
    {
        destroy(head->next);
    }
    free(head);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        if (hashTable[i] != NULL)
        {    
            destroy(hashTable[i]);
        }
    }
    return true;
}
