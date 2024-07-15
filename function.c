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
void displayMainMenu()
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
void manageDataMenu()
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
void languageToolMenu()
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
void manageData(Entry dictionary[], int *entryCount)
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
        case 10:
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
void displayEntry(Entry dictionary)
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
void sortEntry(Entry dictionary[])
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

int checkEntry(Entry dictionary[], int entryCount, String20 language, String20 translation, int indexFound[])
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
    }

    return count;
}

/**
 * function addEntry adds new entry to the array of struct dictionary[]
 *
 * @param dictionary - array of struct
 * @param entryCount - total number of struct in dictionary
 */
void addEntry(Entry dictionary[], int *entryCount)
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
void addTranslation(Entry dictionary[], int entryCount)
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
void displayAll(Entry dictionary[], int entryCount)
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

void modifyEntry(Entry dictionary[], int entryCount)
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
void deleteTranslation(Entry dictionary[], int *entryCount)
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

void deleteEntry(Entry dictionary[], int *entryCount)
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

void searchWord(Entry dictionary[], int entryCount)
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
void searchTranslation(Entry dictionary[], int entryCount)
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
void exportFile(Entry dictionary[], int entryCount)
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
 * function import File IMPORTS DATA 
 * @param dictionary - array of struct
 * @param entryCount - total nubmer of struct in dictionary
 *
 */
 void importFile()          //add to menu - will test tom
 {
    FILE *fp;  
    String20 file_name;

    printf("\n[EXPORT]\n\n");
    printf("Enter filename:");
    scanf("%s", file_name);                //ask for file name
    //fopen

    //IS THERE CURRENT DATA
    //*yes
            //verify one by one
    //*no


    fclose(fp);


 }


void languageTool()
{
	int langChoice;
	
	do
	{
		languageToolMenu();		//display menu
		scanf("%d", &langChoice);
		
		switch(langChoice)
		{
			case 1:				//identify main language
				printf("success");
				break;
			case 2:					//simple translation
				printf("sucess");
				break;
			case 3:					//exit
				return;
			default:
            	printf("Invalid choice. Please try again.\n");
            	break;
		}	
		
	} while (langChoice != 3);
	
}

// ALMOST DONE ASLDKJFLASKDJFLAKSDJFLKSDFJ