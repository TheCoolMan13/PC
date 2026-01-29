#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f1(char s1[], char s2[], char s3[])
{
    int i;
    for (i = 0; i < strlen(s1); i++)
    {

        if (s1[i] == s2[i])
        {
            s3[i] = s1[i];
        }
        else
        {
            s3[i] = '\0';
            return;
        }
    }
    s3[i] = '\0';
}

int main()
{
    char s1[100], s2[100], s3[100];

    printf("Introduceti primul sir de caractere: \n");
    fgets(s1, sizeof(s1), stdin);
    printf("Introduceti al doilea sir de caractere: \n");
    fgets(s2, sizeof(s2), stdin);

    if (s1[0] != s2[0])
        printf("%c", '\0');
    else
    {
        f1(s1, s2, s3);
        printf("Sirul comun este: %s\n", s3);
    }

    return 0;
}