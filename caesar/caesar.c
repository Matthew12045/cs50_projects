#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rotate(char c, int key);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    // Make sure every character in argv[1] is a digit

    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isdigit(argv[1][i]) || atoi(argv[1]) <= 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`

    int key = atoi(argv[1]);

    // Prompt user for plaintext

    string text = get_string("plain text: ");

    // For each character in the plaintext:
    // Rotate the character if it's a letter
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            text[i] = rotate(text[i], key);
        }
    }
    printf("ciphertext: %s\n", text);
}

char rotate(char c, int key)
{
    if (islower(c))
    {
        return 'a' + (c - 'a' + key) % 26;
    }
    else if (isupper(c))
    {
        return 'A' + (c - 'A' + key) % 26;
    }
    return c;
}
