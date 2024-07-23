#include <stdio.h>
#include <string.h>


int main() {

    char string[150];

    fgets(string,150,stdin);

    printf("%d", strcspn(string, "\n"));
}


