#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string strtolower(string str);
string strtoupper(string str);
bool validateKey(string key);
char encipher(char c, string key);

int main(int argc, string argv[])
{

    // get the key using command line arguments
    // validate the key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // convert the key to be all lowercase letters
    string key = strtolower(argv[1]);
    if (!validateKey(key))
    {
        return 1;
    }
    // prompt the user for the plain text
    string text = get_string("plaintext: ");
    // encipher the text
    int textlen = strlen(text);
    for (int i = 0; i < textlen; i++)
    {
        if (isalpha(text[i]))
        {
            text[i] = encipher(text[i], key);
        }
    }
    // print out the ciphered text
    printf("ciphertext: %s\n", text);
}

string strtolower(string str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

string strtoupper(string str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

bool validateKey(string key)
{
    int n = strlen(key);
    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 0;
            }
        }
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetical characters.\n");
            return 0;
        }
    }
    return 1;
}

char encipher(char c, string key)
{
    if (islower(c))
    {
        key = strtolower(key);
        return key[c - 'a'];
    }
    else if (isupper(c))
    {
        key = strtoupper(key);
        return key[c - 'A'];
    }
    return c;
}
