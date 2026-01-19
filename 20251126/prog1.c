#include <stdio.h>
/*
Strlen at home
*/

int myStrlen1(char *p)
{
    // cat timp n-am ajuns la \0 adaug 1 la contor
    char *aux = p;
    int contor = 0;
    while (aux)
    {
        if (*aux == '\0')
        {
            return contor;
        }
        contor++;
        aux++;
    }
    return 0;
}

int main(void)
{
    char s[2020];
    scanf("%s", s);
    char *p = s;
    int lungime = myStrlen1(p);
    printf("%d" , lungime);
    return 0;
}