#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 150
#define MAX_LANG_LEN 20
#define MAX_TRANS_LEN 20
#define MAX_PAIRS 10

typedef char String20[20];
typedef char String30[30];

typedef struct
{
    char language[MAX_LANG_LEN];
    char translation[MAX_TRANS_LEN];
} TranslationPair;

typedef struct
{
    TranslationPair pairs[10];
    int count;
} Entry;

void displayMainMenu();
void manageDataMenu();
void languageToolMenu();
void displayEntry(Entry dictionary);
int checkEntry(Entry dictionary[], int entryCount, String20 language, String20 translation, int indexFound[]);
void addEntry(Entry dictionary[], int *entryCount);
void addTranslation(Entry dictionary[], int entryCount);
void manageData(Entry dictionary[], int *entryCount);
void displayAll(Entry dictionary[], int entryCount);
void sortEntry(Entry *dictionary);
void modifyEntry(Entry dictionary[], int entryCount);
void deleteTranslation(Entry dictionary[], int *entryCount);
void deleteEntry(Entry dictionary[], int *entryCount);
void searchWord(Entry dictionary[], int entryCount);
void searchTranslation(Entry dictionary[], int entryCount);
void exportFile(Entry dictionary[], int entryCount);
void importFile();
void languageTool();            //add parameters
