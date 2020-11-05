// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
// Made it 26 to represent each letter in alphabet
const unsigned int N = 25;

// Hash table
node *table[N];

int num_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //see which bin the word is in by HASHING
    int word_key = hash(word);

    //go to bin
    //create tmp pointer to node to check each node
    node *cursor = table[word_key];

    //bottom line does not work since it does not check the last node in the linked list
    //when it gets to last node, next -> NULL and therefore it will not check that node
    //while (cursor -> next != NULL)

    //this new line checks until cursor points at NULL
    while (cursor != NULL)
    {
        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }

        //move to next node
        cursor = cursor -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return(tolower(word[0]) - 'a');
}

// Loads dictionary into memory, returning true if successful else false
// Load into HASH TABLE
bool load(const char *dictionary)
{
    //open
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        return false;
    }

    //dictionary.h defines max word as 45 chars
    //create buffer to store words from dictionary
    char word_buffer[LENGTH + 1];

    //keep reading strings from dictionary until EOF (all of words in dictionary)
    while (fscanf(source, "%s", word_buffer) != EOF)
    {
        //create node (n) & allocate enough memory for a node
        node *n = malloc(sizeof(node));

        //check if enough memory
        if (n != NULL)
        {
            //(destination, source)
            strcpy(n -> word, word_buffer);
            n -> next = NULL;
        }
        else
        {
            return false;
        }

        if (table[(hash(word_buffer))] == NULL)
        {
            //places word into hash table in appropriate "bin"
            table[hash(word_buffer)] = n;
        }
        //need to create chain if bucket already filled
        else
        {
            //new node point to what table[0] is point at
            n -> next = table[hash(word_buffer)];

            //table[0] point to node n
            table[hash(word_buffer)] = n;
        }

        num_words += 1;

    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (num_words > 0)
    {
        return num_words;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //see if cleared all memory
    int counter = 0;

    for (int j = 0; j <= N; j++)
    {
        node *cursor = table[j];
        node *tmp = table[j];

        //node *head = table[j];
        //node *cursor = head;
        //node *tmp = head;

        //this while loop frees last node too
        while (cursor != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }
    }

    return true;

}
