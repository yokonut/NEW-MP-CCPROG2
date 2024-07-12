#include "function.c"

int main()
{
    Entry dictionary[MAX_ENTRIES];
    int entryCount = 0;
    int exit = 0;
    char choice;

    do
    {
        displayMainMenu();
        scanf(" %c", &choice);
        printf("\n");

        switch (choice)
        {
        case '1':
            printf("\e[1;1H\e[2J");
            manageData(dictionary, &entryCount);
            break;
        case '2':
            languageToolMenu();
            break;
        case '3':
            printf("Exiting... Goodbye!\n");
            exit = 123;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (exit == 0);

    return 0;
}