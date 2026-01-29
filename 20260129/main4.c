#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*

Sa se scrie o functie cu urmatorul antent
char *string_replace_dynamic(const char *where, const char *what, const char *replace)
Functia inlocuieste fiecare aparitie a string-ului what in string-ul where cu string-ul replace. Funcția va returna noul string obținut, alocat dinamic, și NULL în caz de eroare sau în cazul în care string-ul what nu apare în string-ul where.

char s1[] = "Acesta este un string si un string este terminat cu 0x00";
char s2[] = "string";
char s3[] = "sir de caractere";
char *p = string_replace(s1, s2, s3);
p devine un string alocat dinamic cu urmatorul continut: "Acesta este un sir de caractere si un sir de caractere este terminat cu 0x00";
s1, s2, s3 - raman neschimbate
r = 2

*/

char *string_replace_dynamic(const char *where, const char *what, const char *replace)
{
    if (!where || !what || !replace)
        return NULL;

    int contor_aparitii = 0;
    const char *tmp = where;
    while ((tmp = strstr(tmp, what)))
    {
        contor_aparitii++;
        tmp += strlen(what);
    }
    // printf("Aparitii : %d", contor_aparitii);
    if (contor_aparitii == 0)
        return NULL;

    char *result = (char *)malloc((((strlen(replace) - strlen(what)) * contor_aparitii) + strlen(where) + 1) * sizeof(char));
    char *p = result;
    while (*where)
    {
        if (strstr(where, what) == where)
        {
            strcpy(p, replace);
            where += strlen(what);
            p += strlen(replace);
        }
        else
        {
            *p++ = *where++;
        }
    }
    *p = '\0';
    return result;
    free(result);
}

int main()
{

    char s1[] = "Acesta este un string si un string este terminat cu 0x00";
    char s2[] = "string";
    char s3[] = "sir de caractere";
    char *p = string_replace_dynamic(s1, s2, s3);
    printf("%s", p);
    free(p);
    return 0;
}