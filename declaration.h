#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ENTRIES 150
#define MAX_LANG_LEN 20
#define MAX_TRANS_LEN 20
#define MAX_PAIRS 10

typedef char String20[20];
typedef char String30[30];
typedef char String150[150];

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

struct langTag {
    String20 iLanguage;
    int nWord;                  //number of times it appears in phrase
};

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
//MY PART
void importFile(Entry dictionary[], int *entryCount);
int tokenize(char origphrase[], String30 tokens[MAX_ENTRIES]);			//char origphrase[] correct
int matchTranslation(struct langTag ltags[], int lang_count, const char *language);
void identifyLanguage(Entry dictionary[], int entryCount);
void simpleTranslation(Entry dictionary[], int entryCount);
void languageTool(Entry dictionary[], int entryCount);

/*
void importFile();
int tokenize(String150 origphrase);
int matchTranslation(Entry dictionary[], int entryCount, /*struct langTag, int lang_index, int i, int j);
void identifyLanguage(entryCount);
void simpleTranslation(entryCount);
void languageTool();           
*/