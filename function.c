#include "declaration.h"

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
            addEntry(dictionary, entryCount);
            break;
        case 2:
            addTranslation(dictionary, *entryCount);
            break;
        case 3:
            // Implement Remove Entry functionality here
            break;
        case 4:
            // Implement View All Entries functionality here
            break;
        case 5:
            return; // Back to Main Menu
        case 6:
            displayAll(dictionary, *entryCount);
            break; // Back to Main Menu
        case 7:
            return; // Back to Main Menu
        case 8:
            return; // Back to Main Menu
        case 9:
            return; // Back to Main Menu
        case 10:
            return; // Back to Main Menu
        case 11:
            return; // Back to Main Menu
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (manageChoice != 5);
}

void displayEntry(Entry dictionary)
{
    int i, j;

    for (i = 0; i < dictionary.count; i++)
    {
        printf("%d. Language: %s, Translation: %s\n", i + 1, dictionary.pairs[i].language, dictionary.pairs[i].translation);
    }
}

void sortEntry(Entry *dictionary)
{
    int i, j;
    int min;
    TranslationPair temp;
    for (i = 0; i < dictionary->count - 1; i++)
    {
        min = i;

        for (j = i + 1; j < dictionary->count; j++)
        {
            if (strcmp(dictionary->pairs[min].language, dictionary->pairs[j].language) > 0)
                min = j;
        }

        if (min != i)
        {
            temp = dictionary->pairs[i];
            dictionary->pairs[i] = dictionary->pairs[min];
            dictionary->pairs[min] = temp;
        }
    }
}

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
    printf("Enter translation: ");
    scanf("%s", translation);

    totalFound = checkEntry(dictionary, *entryCount, language, translation, indexFound);

    if (totalFound > 0)
    {
        printf("=====================================\n");
        printf("ENTRY ALREADY EXISTS\n");
        printf("=====================================\n");
        for (i = 0; i < totalFound; i++)
        {
            printf("ENTRY %d:\n", i + 1);
            displayEntry(dictionary[indexFound[i]]);
        }

        do
        {
            printf("Is this a new entry? (Y/N) : \n");
            scanf(" %c", &response);
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
    printf("Enter translation of existing entry: ");
    scanf("%s", translation);

    totalFound = checkEntry(dictionary, entryCount, language, translation, indexFound);

    if (totalFound == 0)
    {
        printf("=====================================\n");
        printf("No entry found with the given language and translation\n");
        printf("Please use the ADD ENTRY OPTION (1)\n");
        printf("=====================================\n");
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
            if (response > 1 && response > totalFound)

                printf("INVALID NUMBER PLEASE ENTER AGAIN! \n");

        } while (response > 1 && response > totalFound);

        entryIndex = indexFound[response - 1];

        printf("Enter pair language: ");
        scanf("%s", pLanguage);
        printf("Enter pair translation: ");
        scanf("%s", pTranslation);

        strcpy(dictionary[entryIndex].pairs[dictionary[entryIndex].count].language, pLanguage);
        strcpy(dictionary[entryIndex].pairs[dictionary[entryIndex].count].translation, pTranslation);
        dictionary[entryIndex].count++;

        do
        {
            printf("Do you want to add another pair? (Y/N): ");
            scanf(" %c", &response);
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

void displayAll(Entry dictionary[], int entryCount)
{
    int i, j;
    printf("ALL ENTRIES :\n");
    for (i = 0; i, entryCount; i++)
    {
        printf("ENTRY %d\n", i + 1);
        sortEntry(&dictionary[i]);
        displayEntry(dictionary[i]); 
    }
}