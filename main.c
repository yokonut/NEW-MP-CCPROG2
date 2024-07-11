#include "function.c"

int main()
{
    Entry dictionary[MAX_ENTRIES];
    int entryCount = 0;
    int choice;

    do
    {
        displayMainMenu();
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            manageData(dictionary, &entryCount);
            break;
        case 2:
            languageToolMenu();
            break;
        case 3:
            printf("Exiting... Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }while(choice != 1 && choice != 2 && choice != 3);

    return 0;
}