/*

Sa se scrie o functie cu urmatorul antent
uint32_t string_replace(char *where, const char *what, const char *replace)
Functia inlocuieste fiecare aparitie a string-ului what in string-ul where cu string-ul replace. 
Se considera ca zona de memorie a lui where este suficient de mare ca sa poata contine noul string. 
Functia returneaza numarul de inlocuiri

char s1[1000];
char s2[] = "string";
char s3[] = "sir de caractere";
strcpy(s1, "Acesta este un string si un string este terminat cu 0x00");
int r = string_replace(s1, s2, s3);
s1 devine "Acesta este un sir de caractere si un sir de caractere este terminat cu 0x00";
s2, s3 - raman neschimbate
r = 2
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint32_t string_replace(char *where, const char *what, const char *replace)
{
    int num_replace = 0;
    for(int i = 0 ; i < strlen(where) ; i++)
    {
        if(strncmp(&where[i], what, strlen(what)) == 0)
        {
            num_replace++;
            int len_what = strlen(what);
            int len_replace = strlen(replace);
            int len_where = strlen(where);

            if(len_replace > len_what)
            {
                for(int j = len_where ; j >= i + len_what ; j--)
                {
                    where[j + (len_replace - len_what)] = where[j];
                }
            }
            else if(len_replace < len_what)
            {
                for(int j = i + len_what ; j <= len_where ; j++)
                {
                    where[j - (len_what - len_replace)] = where[j];
                }
            }

            for(int k = 0 ; k < len_replace ; k++)
            {
                where[i + k] = replace[k];
            }
            i += len_replace - 1;
        }

    }
    return num_replace;
}

    int main()
{
    char s1[1000];
    char s2[] = "string";
    char s3[] = "sir de caractere";
    strcpy(s1, "Acesta este un string si un string este terminat cu 0x00");

    int r = string_replace(s1, s2, s3);
    printf("Result: %d\n", r);
    return 0;
}