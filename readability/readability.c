#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int countWords(string text);
int countLetters(string text);
int countSentences(string text);

int main(void)
{
    // Prompt the user for some text

    string text = get_string("Text :");

    // Count the number of letters, words, and sentences in the text

    int letters = countLetters(text);
    int words = countWords(text);
    int sentences = countSentences(text);

    // Compute the Coleman-Liau index

    float L = ((float)letters / words) * 100;
    float S = ((float)sentences / words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    index = round(index);

    // Print the grade level
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
        printf("Grade %i\n", (int) index);
    }
}

int countWords(string text)
{
    int n = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isblank(text[i]))
        {
            n++;
        }
    }
    return n + 1;
}

int countLetters(string text)
{
    int n = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            n++;
        }
    }
    return n;
}

int countSentences(string text)
{
    int n = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            n++;
        }
    }
    return n;
}
