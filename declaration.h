#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 100
#define MAX_LANG_LEN 50
#define MAX_TRANS_LEN 50
#define MAX_PAIRS 10


typedef char String20 [20];



typedef struct {
    char language[MAX_LANG_LEN];
    char translation[MAX_TRANS_LEN];
} TranslationPair;

typedef struct {
    TranslationPair pairs[MAX_PAIRS];
    int count;
} Entry;


void displayMainMenu();
void manageDataMenu();
void languageToolMenu();
void displayEntry(Entry dictionary);
int  findEntry(Entry dictionary[], int entryCount, char *language, char *translation, int foundIndices[]);
void addEntry(Entry dictionary[], int *entryCount);
void addTranslation(Entry dictionary[], int entryCount);
void manageData(Entry dictionary[], int *entryCount);
void displayAll(Entry dictionary[], int entryCount);
void sortEntry(Entry *dictionary);


