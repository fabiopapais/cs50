#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool keyCheck(string key);

int main(int argc, string argv[])
{
    // First simple checks
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1; // Return 1 for CS50 check50
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1; // Return 1 for CS50 check50
    }
    else if (keyCheck(argv[1]) == false)
    {
        printf("Usage: ./substitution key\n");
        return 1; // Return 1 for CS50 check50
    }
    else
    {
        // Simple defining the key and making it all uppercase
        char key[strlen(argv[1]) + 1];
        key[strlen(argv[1]) + 1] = '\0';
        for (int x = 0; x < strlen(argv[1]); x++)
        {
            if ((int) argv[1][x] >= 97 && (int) argv[1][x] <= 122)
            {
                key[x] = argv[1][x] - 32;
            }
            else
            {
                key[x] = argv[1][x];
            }
        }

        string plaintext = get_string("plaintext: ");
        char cyphertext[strlen(plaintext)];
        cyphertext[strlen(plaintext)] = '\0';

        char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";

        int index = 0;

        // This block will loop through our plaintext
        for (int i = 0; i < strlen(plaintext); i++)
        {
            bool control = false;
            // Find letter index
            for (int z = 0; z < 26; z++)
            {
                if (tolower(plaintext[i]) == alphabet[z])
                {
                    index = z;
                    control = true;
                }
            }

            // Constructing cyphertext
            if (control == true)
            {
                // if plaintext is lowercase
                if ((int) plaintext[i] >= 97 && (int) plaintext[i] <= 122)
                {
                    cyphertext[i] = key[index] + 32; // adding 32 on ASCII code makes a char lowercase
                }
                else
                {
                    cyphertext[i] = key[index];
                }
            }
            else if (control == false) // For non alphabetical characteres
            {
                cyphertext[i] = plaintext[i];
            }
        }
        printf("ciphertext: %s\n", cyphertext);
    }
}

// Key checks that need a for loop
bool keyCheck(string key)
{
    int length = strlen(key) - 1;

    // loop through the key
    for (int i = 0; i < length; i++)
    {
        if (isdigit(key[i]))
        {
            return false;
        }

        // loop trough the key again searching for repeated characteres
        for (int j = i + 1; key[j] != '\0'; j++)
        {
            if (key[j] == key[i])
            {
                return false;
            }
        }
    }
    return true;
}
