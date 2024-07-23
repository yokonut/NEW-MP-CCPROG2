#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LANG_LEN 20
#define MAX_ENTRIES 50
#define MAX_TOKEN_LENGTH 30
#define MAX_ORIG_LENGTH 150

typedef char String150[MAX_ORIG_LENGTH];
typedef char String30[MAX_TOKEN_LENGTH];

typedef struct
{
    char language[MAX_LANG_LEN];
    char translation[MAX_TOKEN_LENGTH];
} Pair;

typedef struct
{
    Pair pairs[MAX_ENTRIES];
    int count;
} Entry;

int tokenize(String150 origphrase, String30 tokens[MAX_ENTRIES]);

void simpleTranslation(Entry dictionary[], int entryCount)
{
    char sourcelang[MAX_LANG_LEN];
    char destlang[MAX_LANG_LEN];

    String150 origphrase;
    String150 transphrase = {0}; // Proper initialization
    String30 tokens[MAX_ENTRIES];

    int t_size = 0;
    int i, j, index = 0, m;
    int len;

    char c;

    printf("SIMPLE TRANSLATION\n");

    // Get inputs
    printf("Translate from: ");
    scanf("%s", sourcelang);

    printf("Translate to: ");
    scanf("%s", destlang);
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    printf("Input phrase/sentence to translate: ");
    fgets(origphrase, 150, stdin);
    len = strlen(origphrase) - 1;
    if (origphrase[len] == '\n')
        origphrase[len] = '\0';

    t_size = tokenize(origphrase, tokens);

    for (index = 0; index < t_size; index++)
    {
        int found = 0;
        for (i = 0; i < entryCount && !found; i++)
        {
            for (j = 0; j < dictionary[i].count && !found; j++)
            {
                if (strcmp(dictionary[i].pairs[j].language, sourcelang) == 0 && strcmp(dictionary[i].pairs[j].translation, tokens[index]) == 0)
                {
                    for (m = 0; m < dictionary[i].count && !found; m++)
                    {
                        if (strcmp(dictionary[i].pairs[m].language, destlang) == 0)
                        {
                            strcat(transphrase, dictionary[i].pairs[m].translation);
                            strcat(transphrase, " ");
                            found = 1;
                        }
                    }
                }
            }
        }
        if (!found)
        {
            strcat(transphrase, tokens[index]);
            strcat(transphrase, " ");
        }
    }

    // Remove trailing space
    len = strlen(transphrase);
    if (len > 0 && transphrase[len - 1] == ' ')
        transphrase[len - 1] = '\0';

    printf("Translated phrase: %s\n", transphrase);
}

int tokenize(String150 origphrase, String30 tokens[MAX_ENTRIES])
{
    int token_i = 0; // token index
    int i = 0;       // original phrase index
    int j = 0;       // token letter index

    while (origphrase[i] != '\0' && token_i < MAX_ENTRIES)
    {
        if (isalpha(origphrase[i])) // Check if the character is a letter
        {
            if (j < MAX_TOKEN_LENGTH - 1) // Ensure token does not exceed max length
            {
                tokens[token_i][j++] = origphrase[i];
            }
        }
        else
        {
            if (j > 0) // End current token if we have collected any characters
            {
                tokens[token_i][j] = '\0'; // Null-terminate the token
                token_i++;                 // Move to the next token
                j = 0;                     // Reset token letter index
            }
        }
        i++;
    }

    // Handle the last token if there was no trailing non-letter character
    if (j > 0 && token_i < MAX_ENTRIES)
    {
        tokens[token_i][j] = '\0';
        token_i++;
    }

    return token_i;
}
