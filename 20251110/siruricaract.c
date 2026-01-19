/*
Stringuri in C


*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// void printString(const char *str)
// {
//     int index = 0;
//     while(str[index] != '\0'){
//         putchar(str[index]);
//         index++;
//     }
//     putchar('\n');
// }
void printString(const char *str)
{
    while (*str != '\0')
    {
        putchar(*str);
        str++;
    }
}

int main(void)
{
    char str[100];
    // scanf("%9s" , str);
    // printf("Stringul meu este %s\n " , str);

    /*
    char *fgets(char *str, int size, stdin);
    -> s sau NULL

    */

    if (fgets(str, sizeof(str), stdin) != NULL)
    { // printString(str);
        printf("Stringul meu este: %s\n", str);
    }
    else
    {
        printf("Eroare la citirea stringului\n");
    }
    return 0;
}