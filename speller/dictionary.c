// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Keep track of the number of words loaded
unsigned int word_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 50000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Buffer to store a lowercase version of the word
    char lower_word[LENGTH + 1];
    int length = strlen(word);

    // Convert the word to lowercase
    for (int i = 0; i < length; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[length] = '\0'; // Null-terminate the string

    // Hash the word to get the index
    unsigned int index = hash(lower_word);

    // Traverse the linked list at that hash table index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Compare character by character to stop early if possible
        if (strncmp(cursor->word, lower_word, LENGTH) == 0)
        {
            return true; // Word found
        }
        cursor = cursor->next; // Move to the next node
    }

    // Word not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash_value = 0;
    while (*word != '\0')
    {
        hash_value = (hash_value << 5) + tolower(*word); // Left shift and add lowercased character
        word++;
    }
    return hash_value % N; // Return a hash value within the larger table size
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    // Buffer to hold each word from the dictionary
    char word[LENGTH + 1];

    // Read each word from the file
    while (fscanf(dic, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(dic);
            printf("Not enough memory.\n");
            return false; // Memory allocation failed
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash the word to get an index
        unsigned int index = hash(word);

        // Insert the node into the hash table (handle collision with chaining)
        if (table[index] == NULL)
        {
            table[index] = new_node; // No collision
        }
        else
        {
            new_node->next = table[index]; // Insert at the beginning of the list (chaining)
            table[index] = new_node;
        }

        // Increment the word count
        word_count++;
    }

    // Close the dictionary file
    fclose(dic);
    return 1;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the words counted.
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over each bucket
    for (int i = 0; i < N; i++)
    {
        // Free each linked list in the bucket
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp); // Free each node
        }
    }

    return true;
}
