#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string text = get_string("Text: ");
    int textLength = strlen(text);

    // Variables declaration
    int lettersCount = 0;
    int wordsCount = 0;
    int sentencesCount = 0;

    float averageLetters = 0;
    float averageSentences = 0;

    float index = 0;

    int readability = 0;

    // Loop that iterates through the text
    for (int i = 0; i < textLength; i++)
    {
        text[i] = tolower(text[i]); // Making everything lowercase to make validating easier

        if (text[i] >= 'a' && text[i] <= 'z')
        {
            lettersCount++; // letter identified

            if (text[i + 1] == '.' || text[i + 1] == '!' || text[i + 1] == '?')
            {
                sentencesCount++; // sentence identified
            }
        }

        if ((text[i] == ' ' && text[i - 1] != '.') || text[i] == '.')
        {
            wordsCount++; // word identified
        }
    }

    averageLetters = lettersCount * (100 / (float) wordsCount); // Average letters per 100 words
    averageSentences = sentencesCount * (100 / (float) wordsCount); // Average sentences per 100 letters

    printf("%i %i %i \n", wordsCount, sentencesCount, lettersCount);
    printf("averageLetters: %f averageSentences: %f \n", averageLetters, averageSentences);

    // Coleman-Liau index calc
    index = 0.0588 * averageLetters - 0.296 * averageSentences - 15.8;

    readability = round(index);

    // Formatting block
    if (readability >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (readability < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", readability);
    }
}
