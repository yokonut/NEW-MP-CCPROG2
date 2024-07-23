/*********************************************************************************************************
This is to certify that this project is our own work, based on our personal efforts in studying and applying the concepts
learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The
program was run, tested, and debugged by our own efforts. We further certify that we have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
 KO YOHAN, DLSU ID# 11849020
 SOPHIA ILUSTRE, DLSU ID#
*********************************************************************************************************/

#include "declaration.h"

/*
    Display for Main Menu

*/

void 
displayMainMenu()
{
    printf("=====================================\n");
    printf("        Welcome to the Dictionary    \n");
    printf("=====================================\n");
    printf("1. Manage Data\n");
    printf("2. Language Tool\n");
    printf("3. Exit\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
}
/*
    Display for manage Date Menu

*/
void 
manageDataMenu()
{

    printf("=====================================\n");
    printf("          Manage Data Menu           \n");
    printf("=====================================\n");
    printf("1. Add Entry\n");
    printf("2. Add Translations\n");
    printf("3. Modify Entry\n");
    printf("4. Delete Entry\n");
    printf("5. Delete Translation\n");
    printf("6. Display All Entries\n");
    printf("7. Search Word\n");
    printf("8. Search Translation\n");
    printf("9. Export\n");
    printf("10. Import\n");
    printf("11. Back to Main Menu\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
}

/*
    Display for language tool Menu

*/
void 
languageToolMenu()
{

    printf("=====================================\n");
    printf("          Language Tool Menu         \n");
    printf("=====================================\n");
    printf("1. Identify Main Language\n");
    printf("2. Simple Translation\n");
    printf("3. Back to Main Menu\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
}

/**
 *  function manageData scans the user's choice of option in the manageData menu
 *
 *
 * @param dictionary - contains an array of struct
 * @param entryCount  - contains the total number of entries
 */
void 
manageData(Entry dictionary[], 
            int *entryCount)
{
    int manageChoice;
    do
    {
        manageDataMenu();
        scanf("%d", &manageChoice);
        switch (manageChoice)
        {
        case 1:
            printf("\e[1;1H\e[2J");
            addEntry(dictionary, entryCount);
            break;
        case 2:
            printf("\e[1;1H\e[2J");
            if (*entryCount > 0)
                addTranslation(dictionary, *entryCount);
            else
                printf("NO ENTRY\n");
            break;
        case 3:
            printf("\e[1;1H\e[2J");
            if (*entryCount > 0)
                modifyEntry(dictionary, *entryCount);
            else
                printf("NO ENTRY\n");
            break;
        case 4:
            printf("\e[1;1H\e[2J");
            if (*entryCount > 0)
                deleteEntry(dictionary, entryCount);
            else
                printf("NO ENTRY\n");
            break;
        case 5:
            printf("\e[1;1H\e[2J");
            if (*entryCount > 0)
                deleteTranslation(dictionary, entryCount);
            else
                printf("NO ENTRY\n");
            break;
        case 6:
            printf("\e[1;1H\e[2J");
            if (*entryCount > 0)
                displayAll(dictionary, *entryCount);
            else
                printf("NO ENTRY\n");
            break; // Back to Main Menu
        case 7:
            printf("\e[1;1H\e[2J");
            if (*entryCount > 0)
                searchWord(dictionary, *entryCount);
            else
                printf("NO ENTRY\n");
            break; // Back to Main Menu
        case 8:
            printf("\e[1;1H\e[2J");
            if (*entryCount > 0)
                searchTranslation(dictionary, *entryCount);
            else
                printf("NO ENTRY\n");
            break; // Back to Main Menu
        case 9:
            printf("\e[1;1H\e[2J");
            if (*entryCount > 0)
                exportFile(dictionary, *entryCount);
            else
                printf("NO ENTRY\n");
            break;
        case 10: // import
            printf("\e[1;1H\e[2J");
            importFile(dictionary, entryCount);
            break;
        case 11:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (manageChoice != 11);
}

/**
 * function displayEntry only display ONE of the entry
 *
 * @param dictionary - a struct containing all the pairs and count
 */
void 
displayEntry(Entry dictionary)
{
    int i, j;

    for (i = 0; i < dictionary.count; i++)
    {

        printf("%d. Language: %s, Translation: %s\n", i + 1, dictionary.pairs[i].language, dictionary.pairs[i].translation);
    }
}

/**
 *  the function sort entry sorts all the pairs according ALPHABETICALLY
 * @param dictionary - array of struct
 */
void 
sortEntry(Entry dictionary[])
{
    int i, j;

    TranslationPair temp;
    String20 tempLang1;
    String20 tempLang2;

    for (i = 0; i < dictionary->count - 1; i++)
    {
        for (j = i + 1; j < dictionary->count; j++)
        {
            strcpy(tempLang1, dictionary->pairs[i].language);
            strcpy(tempLang2, dictionary->pairs[j].language);

            if (strcmp(tempLang1, tempLang2) > 0)
            {
                temp = dictionary->pairs[i];
                dictionary->pairs[i] = dictionary->pairs[j];
                dictionary->pairs[j] = temp;
            }
        }
    }
}

/**
 * function checkEntry checks if an existing entry is in the array of struct
 *
 * @param dictionary - array of struct
 * @param entryCount - total number of struct in dictionary
 * @param language - string to search in dictionary
 * @param translation - string to search in dictinonary
 * @param indexFound - array of integers which stores the found indicies
 */

int 
checkEntry(Entry dictionary[], 
            int entryCount, 
            String20 language, 
            String20 translation, 
            int indexFound[])
{
    int i;
    int count = 0;

    for (i = 0; i < entryCount; i++)
    {
        if (strcmp(dictionary[i].pairs[0].language, language) == 0 && strcmp(dictionary[i].pairs[0].translation, translation) == 0)
        {
            indexFound[count] = i;
            count++;
        }
        else
            return -1;
    }

    return count;
}

/**
 * function addEntry adds new entry to the array of struct dictionary[]
 *
 * @param dictionary - array of struct
 * @param entryCount - total number of struct in dictionary
 */
void 
addEntry(Entry dictionary[], 
            int *entryCount)
{
    String20 language;
    String20 translation;
    char response;
    int totalFound;
    int indexFound[MAX_ENTRIES];
    int i;

    printf("Enter language: ");
    scanf("%s", language);
    printf("\n");
    printf("Enter translation: ");
    scanf("%s", translation);
    printf("\n");

    totalFound = checkEntry(dictionary, *entryCount, language, translation, indexFound);

    if (totalFound > 0)
    {
        printf("ENTRY ALREADY EXISTS\n");
        for (i = 0; i < totalFound; i++)
        {
            printf("ENTRY %d:\n", i + 1);
            displayEntry(dictionary[indexFound[i]]);
        }

        do
        {
            printf("Is this a new entry? (Y/N) : \n");
            scanf(" %c", &response);
            printf("\n");
            if (response != 'y' && response != 'Y' && response != 'n' && response != 'N')
                printf("INVALID RESONSE ENTER AGAIN!!\n");
        } while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');

        switch (response)
        {
        case 'y':
        case 'Y':
            strcpy(dictionary[*entryCount].pairs[0].language, language);
            strcpy(dictionary[*entryCount].pairs[0].translation, translation);
            dictionary[*entryCount].count = 1;
            (*entryCount)++;
            printf("ADDED NEW ENTRY\n");
            printf("=====================================\n");
            break;
        case 'n':
        case 'N':
            break;
        }
    }

    else
    {
        strcpy(dictionary[*entryCount].pairs[0].language, language);
        strcpy(dictionary[*entryCount].pairs[0].translation, translation);
        dictionary[*entryCount].count = 1;
        (*entryCount)++;
        printf("ADDED NEW ENTRY\n");
        printf("=====================================\n");
    }

    printf("Do you want to add more Entry? (Y/N) : ");
    do
    {
        scanf(" %c", &response);
        if (response != 'y' && response != 'Y' && response != 'n' && response != 'N')
            printf("INVALID RESONSE ENTER AGAIN!!\n");
        else
        {
            switch (response)
            {
            case 'y':
            case 'Y':
                addEntry(dictionary, entryCount);
                break;
            }
        }
    } while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');
}

/**
 * function addTranslation adds a pair of language and translation to an already existing entry
 *
 * @param dictionary - array of struct
 * @param entryCount - total number of struct
 */
void 
addTranslation(Entry dictionary[], 
                int entryCount)
{
    String20 language;
    String20 translation;
    String20 pLanguage;
    String20 pTranslation;
    int indexFound[MAX_ENTRIES];
    int totalFound;
    int i;
    int entryIndex;
    int response;

    printf("Enter language of existing entry: ");
    scanf("%s", language);
    printf("\n");
    printf("Enter translation of existing entry: ");
    scanf("%s", translation);
    printf("\n");

    totalFound = checkEntry(dictionary, entryCount, language, translation, indexFound);

    if (totalFound == 0)
    {
        printf("No entry found please use the ADD ENTRY OPTION (1)\n");
    }
    else
    {
        printf("Entries Found:\n");
        for (i = 0; i < totalFound; i++)
        {
            printf("Entry %d:\n", i + 1);
            displayEntry(dictionary[indexFound[i]]);
        }

        do
        {
            printf("Enter the number of the entry to add translation to : ");
            scanf("%d", &response);
            printf("\n");
            if (response > 1 && response > totalFound)

                printf("INVALID NUMBER PLEASE ENTER AGAIN! \n");

        } while (response > 1 && response > totalFound);

        entryIndex = indexFound[response - 1];

        printf("Enter pair language: ");
        scanf("%s", pLanguage);
        printf("\n");
        printf("Enter pair translation: ");
        scanf("%s", pTranslation);
        printf("\n");

        strcpy(dictionary[entryIndex].pairs[dictionary[entryIndex].count].language, pLanguage);
        strcpy(dictionary[entryIndex].pairs[dictionary[entryIndex].count].translation, pTranslation);
        dictionary[entryIndex].count++;

        do
        {
            printf("Do you want to add another pair? (Y/N): ");
            scanf(" %c", &response);
            printf("\n");
            if (response != 'y' && response != 'Y' && response != 'n' && response != 'N')
            {
                printf("INVALID ANSWER PLEASE TRY AGAIN\n");
            }
            else if (response == 'y' || response == 'Y')
            {

                addTranslation(dictionary, entryCount);
            }
        } while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');
    }
}

/**
 *  function displayAll displays all the entries in the array of struct dictionary
 *
 * @param dictionary - array of struct
 * @param entryCount - total number of struct in dictionary
 */
void 
displayAll(Entry dictionary[], 
            int entryCount)
{
    int i, j;
    int page = 0;
    char response;
    int exit = 0;

    if (entryCount == 0)
    {
        printf("NO ENTRY TO DISPLAY\n");
    }
    else
    {
        while (exit == 0)
        {
            printf("\e[1;1H\e[2J");
            printf("ENTRY %d out of %d: \n", page + 1, entryCount);
            sortEntry(&dictionary[page]);
            displayEntry(dictionary[page]);
            if (page == 0 && entryCount > 1)
            {
                printf("ENTER [N] NEXT [X] EXIT : ");
                scanf(" %c", &response);
                printf("\n");
                switch (response)
                {
                case 'n':
                case 'N':
                    page++;
                    break;
                case 'x':
                case 'X':
                    exit = 1123;
                    break;
                default:
                    printf("INVALID INPUT!\n");
                }
            }
            else if (page > 0 && page < entryCount - 1)
            {
                printf("ENTER [N] NEXT [P] PREVIOUS [X] EXIT : ");
                scanf(" %c", &response);
                printf("\n");
                switch (response)
                {
                case 'n':
                case 'N':
                    page++;
                    break;
                case 'p':
                case 'P':
                    page--;
                    break;
                case 'x':
                case 'X':
                    exit = 1123;
                    break;
                default:
                    printf("INVALID INPUT!\n");
                }
            }
            else if (page == 0 && entryCount == 1)
            {
                printf("ENTER [X] EXIT :");
                scanf(" %c", &response);
                printf("\n");
                switch (response)
                {
                case 'x':
                case 'X':
                    exit = 123;
                    break;
                default:
                    printf("INVALID INPUT!\n");
                }
            }
            else if (page == entryCount - 1)
            {
                printf("ENTER [P] PREVIOUS [X] EXIT : ");
                scanf(" %c", &response);
                printf("\n");
                switch (response)
                {
                case 'p':
                case 'P':
                    page--;
                    break;
                case 'x':
                case 'X':
                    exit = 1123;
                    break;
                default:
                    printf("INVALID INPUT!\n");
                }
            }
        }
    }
}

/**
 * function modifyEntry modifies an already existing entry
 * @param dictionary - array of struct
 * @param entryCount - total number of struct in dictionary
 */

void 
modifyEntry(Entry dictionary[], 
            int entryCount)
{
    int response;
    int response2;
    char response3;
    int exit = 0;
    String20 newLang;
    String20 newTrans;

    displayAll(dictionary, entryCount);
    printf("\nEnter # of entry you want to edit : ");
    scanf("%d", &response);

    if (response < 0 || response > entryCount)
    {
        printf("WRONG INPUT :( \n");
    }
    else
    {
        do
        {
            displayEntry(dictionary[response - 1]);
            printf("Enter # of pair to modify: ");
            scanf("%d", &response2);
            printf("\n");
            if (response > dictionary[response - 1].count && response < 0)
                printf("WRONG INPUT\n");
        } while (response2 > dictionary[response - 1].count && response2 < 0);

        printf("Enter new Language for pair # %d :", response2);
        scanf("%s", newLang);
        printf("Enter new Translation for pair # %d :", response2);
        scanf("%s", newTrans);

        strcpy(dictionary[response - 1].pairs[response2 - 1].language, newLang);
        strcpy(dictionary[response - 1].pairs[response2 - 1].translation, newTrans);
        printf("MODIFIED!! :D \n");
    }

    do
    {
        printf("Do you want to modify another pair? (Y/N) : ");
        scanf(" %c", &response3);

        switch (response3)
        {
        case 'y':
        case 'Y':
            do
            {
                displayEntry(dictionary[response - 1]);
                printf("Enter # of pair to modify\n");
                scanf("%d", &response2);
                printf("\n");
                if (response > dictionary[response - 1].count && response < 0)
                    printf("WRONG INPUT\n");
            } while (response2 > dictionary[response - 1].count && response2 < 0);

            printf("Enter new Language for pair # %d :", response2);
            scanf("%s", newLang);
            printf("Enter new Translation for pair # %d :", response2);
            scanf("%s", newTrans);

            strcpy(dictionary[response - 1].pairs[response2 - 1].language, newLang);
            strcpy(dictionary[response - 1].pairs[response2 - 1].translation, newTrans);
            printf("MODIFIED!! :D \n");
            break;
        case 'n':
        case 'N':
            exit = 123;
            break;
        default:
            printf("INVALID INPUT!\n");
        }

    } while (exit == 0);
}

/**
 * function deleteTranslation deletes a translation in an entry
 * @param dictionary - array of struct
 * @param entryCount - total nubmer of struct in dictionary
 *
 */
void 
deleteTranslation(Entry dictionary[], 
                    int *entryCount)
{
    int response;
    int response2;

    displayAll(dictionary, *entryCount);
    printf("Enter # of entry you want to edit : ");
    scanf("%d", &response);
    printf("\n");

    if (response <= 0 || response > *entryCount)
    {
        printf("WRONG INPUT :( \n");
    }
    else
    {
        do
        {
            displayEntry(dictionary[response - 1]);
            printf("Enter # of pair to delete :");
            scanf("%d", &response2);
            printf("\n");
            if (response2 > dictionary[response - 1].count || response2 <= 0)
                printf("WRONG INPUT\n");
        } while (response2 > dictionary[response - 1].count || response2 <= 0);

        for (int i = response2 - 1; i < dictionary[response - 1].count - 1; i++)
        {
            dictionary[response - 1].pairs[i] = dictionary[response - 1].pairs[i + 1];
        }
        dictionary[response - 1].count--;

        if (dictionary[response - 1].count == 0)
        {
            dictionary[response - 1] = dictionary[*entryCount - 1];
            (*entryCount)--;
        }
        printf("Translation pair deleted!\n");
    }
}

/**
 * function deleteEntry deletes whole entry together with the language-translation pairs if given
 * @param dictionary - array of struct
 * @param entryCount - total nubmer of struct in dictionary
 *
 */

void 
deleteEntry(Entry dictionary[], 
            int *entryCount)
{

    int response;
    int response2;
    char response3;
    String20 newLang;
    String20 newTrans;

    do
    {
        displayAll(dictionary, *entryCount);
        printf("Enter # of entry you want to delete : ");
        scanf("%d", &response);
        printf("\n");
        if (response < 0 || response > *entryCount)
            printf("WRONG INPUT! \n");
    } while (response < 0 || response > *entryCount);

    dictionary[response - 1] = dictionary[*entryCount - 1];
    (*entryCount)--;
    printf("ENTRY DELETED!\n");
}
/**
 * function searchWord searches and displays ALL THE ENTRIES with the given translation
 * @param dictionary - array of struct
 * @param entryCount - total nubmer of struct in dictionary
 *
 */

void 
searchWord(Entry dictionary[], 
            int entryCount)
{
    String20 word;
    char response;
    int i, j;
    int found[entryCount];
    int nfound = 0;
    Entry dictionaryTemp[entryCount];

    printf("Enter word to search: ");
    scanf("%s", word);

    for (i = 0; i < entryCount; i++)
    {
        for (j = 0; j < dictionary[i].count; j++)
        {
            if (strcmp(dictionary[i].pairs[j].translation, word) == 0)
            {
                dictionaryTemp[nfound] = dictionary[i];
                nfound++;
            }
        }
    }

    if (nfound == 0)
    {
        printf("NO DATA FOUND D:\n");
    }
    else
    {
        displayAll(dictionaryTemp, nfound);
    }
}
/**
 * function searchTranslation searches and displays ALL THE ENTRIES with the given language and translation pairs
 * @param dictionary - array of struct
 * @param entryCount - total nubmer of struct in dictionary
 *
 */
void 
searchTranslation(Entry dictionary[], 
                    int entryCount)
{
    int i, j;
    int count = 0;
    String20 language;
    String20 translation;
    int indexFound[entryCount];
    Entry dictionaryTemp[entryCount];

    printf("Enter Language to search: ");
    scanf("%s", language);
    printf("Enter Translation to search");
    scanf("%s", translation);

    for (i = 0; i < entryCount; i++)
    {
        for (j = 0; j < dictionary[i].count; j++)
        {
            if (strcmp(dictionary[i].pairs[j].language, language) == 0 && strcmp(dictionary[i].pairs[j].translation, translation) == 0)
            {
                dictionaryTemp[count] = dictionary[i];
                count++;
            }
        }
    }
    if (count == 0)
    {
        printf("NO DATA FOUND D:\n");
    }
    else
    {
        displayAll(dictionaryTemp, count);
    }
}
/**
 * function exportFile EXPORTS FILE WITH ALL THE
 * @param dictionary - array of struct
 * @param entryCount - total nubmer of struct in dictionary
 *
 */
void 
exportFile(Entry dictionary[], 
            int entryCount)
{
    FILE *fp;
    String30 filename;
    int i, j;
    char cDump;

    printf("\n[EXPORT]\n\n");
    printf("Enter filename:");
    scanf("%c", &cDump);
    fgets(filename, sizeof(filename), stdin); // allow multiple strings as a filename
    filename[strlen(filename) - 1] = '\0';    // assign the last element as NULL

    fp = fopen(filename, "w"); // open file with write file mode
    for (i = 0; i < entryCount; i++)
    {
        for (j = 0; j < dictionary[i].count; j++)
            fprintf(fp, "%s: %s\n", dictionary[i].pairs[j].language,
                    dictionary[i].pairs[j].translation); // write the contents of array of entries to the text file
        fprintf(fp, "\n");
    }
    fclose(fp); // close the file
}

/**
 * function getText
 * @param fp - file pointer
 * @param pLang - string pointer
 * @param pTrans - string pointer
 *@param ch - imported character from file
 */
void 
getText(FILE *fp, 
        String20 *pLang, 
        String20 *pTrans, 
        char ch)
{
    String20 sTemp, sLanguage, sTranslation;
    char cDump;

    sTemp[0] = ch;
    sTemp[1] = '\0';

    fscanf(fp, "%s%c%s", sLanguage, &cDump, sTranslation);

    if (sLanguage[strlen(sLanguage) - 1] == ':')
    {
        sLanguage[strlen(sLanguage) - 1] = '\0';
    }

    strcat(sTemp, sLanguage);
    strcpy(*pLang, sTemp);
    strcpy(*pTrans, sTranslation);
}

/**
 * function importFile IMPORTS DATA from file data type
 * @param dictionary - array of struct
 * @param entryCount - total nubmer of struct in dictionary
 *
 */
void 
importFile(Entry dictionary[], 
                int *entryCount)
{
    FILE *fp;
    String20 file_name;
    char cDump;
    char response;
    int i = 0;
    int j = 0;
    int dCount = 0;

    printf("\n[IMPORT]\n\n");
    printf("Enter filename:");
    scanf("%c", &cDump);
    fgets(file_name, sizeof(file_name), stdin); // ask for file name
    file_name[strlen(file_name) - 1] = '\0';

    // scanf("%s", file_name);

    fp = fopen(file_name, "r"); // fopen
    if (fp != NULL)             // file exists
    {
        if (*entryCount == 0) // no entries yet
        {
            while (!feof(fp) && *entryCount < MAX_ENTRIES) // keep going while eof not reached + entry count not yet exceeded
            {                                              // just list everything
                fscanf(fp, "%c", &cDump);

                if (cDump != '\n' && cDump != EOF)
                {
                    getText(fp, &dictionary[*entryCount].pairs[j].language, &dictionary[*entryCount].pairs[j].translation, cDump);
                    fscanf(fp, "%c", &cDump);
                    dictionary[*entryCount].count++; // equivalent of entry[*n].nPair++;
                    j++;
                    dCount = 0;
                }
                else if (cDump == '\n')
                {
                    dCount++;
                }
                if (dCount == 1)
                {
                    (*entryCount)++;
                    j = 0;
                }
            }
        }

        else if (*entryCount > 0) // there are already existing entries
        {
            while(!feof(fp) && *entryCount < 150)
            {
                fscanf(fp, "%c", &cDump);

                if (cDump != '\n' && cDump != EOF)
                {
                    getText(fp, &dictionary[*entryCount].pairs[j].language, &dictionary[*entryCount].pairs[j].translation, cDump);
                    fscanf(fp, "%c", &cDump);
                    dictionary[*entryCount].count++; // equivalent of entry[*n].nPair++;
                    j++;
                    dCount = 0;
                }
                else if (cDump == '\n')
                {
                    dCount++;
                }

                if (dCount == 1)
                {
                    j = 0;
                    do
                    {
                        printf("\n");

                        for (i = 0; i < dictionary[*entryCount].count; i++)
                        {
                            printf("%s: %s\n", dictionary[*entryCount].pairs[i].language, dictionary[*entryCount].pairs[i].translation);
                        }

                        printf("\n Is this a new entry? [Y/N]");
                        scanf("%c", &response);

                    } while (response != 'Y' && response != 'y' && response != 'N' && response != 'n');

                    if (response == 'Y' || response == 'y') // new entry
                    {
                        (*entryCount)++;
                    }
                    else if (response == 'N' || response == 'n')
                    {
                        for (i = 0; i < dictionary[*entryCount].count; i++)
                        {
                            dictionary[*entryCount].pairs[i].language[0] = '\0';
                            dictionary[*entryCount].pairs[i].translation[0] = '\0'; // clears the information in the specific trans
                        }
                        dictionary[*entryCount].count = 0;
                    }
                }
            }
        }
    }
    else
    { // file does not exist
        printf("ERROR OPENING FILE.\n");
    }

    // SORT FIRST? - Based on the last note in the Export, do not assume that each entry in the file to be imported are already sorted.

    if (*entryCount == MAX_ENTRIES)
    {
        printf("MAX ENTRIES REACHED.\n");
    }

    fclose(fp);
}

/*
 * function tokenize returns number of tokens in phrase
 * @param origphrase - phrase to be tokenized
 * @param tokens[] - array of tokens derived from orig phrase
 */
int 
tokenize(String150 origphrase, 
        String20 tokens[MAX_ENTRIES])
{
    int token_i = 0; // token index
    int i = 0;       // original phrase index
    int j = 0;       // token letter index

    while (origphrase[i] != '\0' && token_i < MAX_ENTRIES)
    {
        if ((origphrase[i] >= 'A' && origphrase[i] <= 'Z') || (origphrase[i] >= 'a' && origphrase[i] <= 'z')) // Check if the character is a letter
        {
            if (j < 30) // Ensure token does not exceed max length
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

/**
 * function matchTranslation returns index where language was found
 * returns index of language in langTag struct
 * @param ltags - array of struct
 * @param lang_count - total number of struct in dictionary
 * @param language - string to search in dictionary
 */

int 
matchTranslation(struct langTag ltags[], 
                    int lang_count, 
                    const char *language)
{

    int i;

    for (i = 0; i < lang_count ; i++)
    {
        if (strcmp(language, ltags[i].iLanguage) == 0)
        {
            return i;
        }
    }

    return -1;
}

/**
 * function sortDescending rearranges structs to sort based on descending nWord count
 * @param ltags - array of struct
 * @param lang_count - total nubmer of struct in ltags
 *
 */
void 
sortDescending(struct langTag ltags[], 
                int lang_count)
{
  int i, j, min;
  struct langTag lTemp;

  for (i = 0; i < lang_count - 1; i++)
  {
    min = i;

    for (j = i + 1; j < lang_count; j++)
    {
      if (ltags[min].nWord < ltags[j].nWord)
        min = j;
    }

    if (i != min)
    {
      lTemp = ltags[i];
      ltags[i] = ltags[min];
      ltags[min] = lTemp;
    }
  }
}

/**
 * function seeMatch identifies main language of string
 * @param dictionary - array of struct
 * @param entryCount - total nubmer of struct in dictionary
 *
 */
int 
seeMatch(Entry dictionary[], 
			int n, 
			String20 sLang, 
			String20 sTrans)
{
  int i;

  for (i = 0; i < dictionary[n].count; i++)
  {
    if (strcmp(sLang, dictionary[n].pairs[i].language) == 0 &&
        strcmp(sTrans, dictionary[n].pairs[i].translation) == 0) //checks if pair exists
    {
      return 1; //found
    }
  }
  return 0; //not found
}

/**
 * function identifyLanguage identifies main language of string
 * @param dictionary - array of struct
 * @param entryCount - total nubmer of struct in dictionary
 *
 */

void 
identifyLanguage(Entry dictionary[], 
                int entryCount)
{
    printf("[IDENTIFY LANGUAGE]\n");

    struct langTag ltags[MAX_LANG_LEN];

    int i, j, k, m;
    int wCount, wDump;
    int tokens_i;

    String150 origphrase;
    int t_size;
    String20 tokens[MAX_ENTRIES];
    int len;

    fgets(origphrase, sizeof(origphrase), stdin);
    len = strlen(origphrase) - 1;
    if (origphrase[len] == '\n')
        origphrase[len] = '\0';

    t_size = tokenize(origphrase, tokens);

    int lang_count = 0;
    int lang_index = 0;
    int max = 0;

    for (tokens_i = 0; tokens_i < t_size; tokens_i++)
    {
        for (i = 0; i < entryCount; i++)
        {
            for (j = 0; j < dictionary[i].count; j++)
            {
                matchTranslation(ltags, lang_count, dictionary[i].pairs[j].language);
                if ((strcmp(dictionary[i].pairs[j].translation, tokens[tokens_i]) == 0) /*match word and token*/ && (lang_index != -1 /*exists*/)) // FOUND WORD- mahal
                {
                    strcpy(ltags[lang_count].iLanguage, dictionary[i].pairs[j].language);
                    ltags[lang_count].nWord++;
                    lang_count++;
                }
            }
        }
    }

    if (lang_count == 0) // if none of the words are found in the array of entries, like “mi casa su casa”, then the result is a message to say that it cannot determine the language.]
    {
        printf("CANNOT DETERMINE LANGUAGE.\n");
    }
    else if (lang_count > 0)
    {
        for(i = 0; i < lang_count; i++)
        {
            wCount = 0;
            for (m = 0; m < t_size; m++)
            {
                wDump = 0;
                for (j = 0; j < entryCount; j++)
                {
                    if(seeMatch(dictionary, j, ltags[i].iLanguage, tokens[m]) == 1)
                    {
                        wDump++;
                    }
                }
            }

            if(wDump > 0)
            {
                wCount++;
            }
            ltags[i].nWord = wCount;
        }
            
        if(lang_count > 1)
            sortDescending(ltags, lang_count);                 //sort language
           
    }

    printf("The main language of text: %s is %s", origphrase, ltags[0].iLanguage);

    for (i = 0; i < lang_count /*IS THIS CPRRECT*/; i++) // ERASE EVERYTHING
    {
        ltags[i].nWord = '\0';
        strcpy(ltags[i].iLanguage, "");
    }

}

/**
 * function simpleTranslation translate a phrase from 1 language to another
 * @param dictionary - array of struct
 * @param entryCount - total number of struct in dictionary
 *
 */
void 
simpleTranslation(Entry dictionary[], 
                    int entryCount)
{
    char sourcelang[MAX_LANG_LEN]; // INPUT DECLARATION
    char destlang[MAX_LANG_LEN];

    String150 origphrase;
    String150 transphrase;        // OUTPUT DECLARATION
    String20 tokens[MAX_ENTRIES]; // for tokenizing

    int t_size = 0; // no of tokens
    int i, j, index = 0, m;
    int found;
    int len;
    char response;
    char c;
    int exit = 0;

    printf("SIMPLE TRANSLATION\n");

    // GET INPUTS
    printf("Translate from: ");
    scanf("%s", sourcelang);

    printf("Translate to: ");
    scanf("%s", destlang);
    while ((c = getchar()) != '\n' && c != EOF)
    {
    } // NOT SURE IF THIS IS ALLOWED pero this clears buffer from scanf to fgets!!

    printf("Input phrase/sentence to translate: ");

    fgets(origphrase, sizeof(origphrase), stdin);
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

    do
    {
        printf("Do you want to translate another phrase? (Y/N) : ");
        scanf(" %c", &response);

        switch (response)
        {
        case 'y':
        case 'Y':
            simpleTranslation(dictionary, entryCount);
            break;

        case 'n':
        case 'N':
            exit = 123;
            break;

        default:
            printf("WRONG INPUT PLEASE TRY AGAIN >:(\n");
        }

    } while (exit == 0);
}

/**
 * function languageTool displays choices in Language Tool Menu
 *@param dictionary - array of structs
 *@param entryCount - total number of struct in dictionary
 */
void 
languageTool(Entry dictionary[], 
                int entryCount)
{
    int langChoice;

    do
    {
        printf("\e[1;1H\e[2J");
        languageToolMenu(); // display menu
        scanf("%d", &langChoice);

        switch (langChoice)
        {
        case 1: // identify main language
            printf("\e[1;1H\e[2J");
            identifyLanguage(dictionary, entryCount); // no & cos we wont edit
            break;
        case 2: // simple translation
            printf("\e[1;1H\e[2J");
            simpleTranslation(dictionary, entryCount);
            break;
        case 3: // exit - everything should be cleared
            return;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

    } while (langChoice != 3);
}