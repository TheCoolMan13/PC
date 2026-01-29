#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Să se scrie o funcție care primește două șiruri
de caractere și le concatenează cu un spațiu
între ele, folosind un bloc de memorie alocat
dinamic pentru rezultat. Funcția va returna
acest bloc de memorie. Să se verifice funcția cu două șiruri de
caractere introduse de la tastatură, fiecare de maxim 100 de caractere.
*/

int main()
{
    char str1[101], str2[101];
    printf("Introduceti primul sir: ");
    fgets(str1, 101, stdin);
    str1[strcspn(str1, "\n")] = 0;

    printf("Introduceti al doilea sir: ");
    fgets(str2, 101, stdin);
    str2[strcspn(str2, "\n")] = 0;

    char *s3 = (char *)malloc((sizeof(str1) + sizeof(str2) + 2) * sizeof(char));

    strcpy(s3, str1);
    strcat(s3, " ");
    strcat(s3, str2);

    printf("S3 este: %s\n", s3);
    free(s3);
    return 0;
}