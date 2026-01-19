#include <stdio.h>

int Mystrcmp(char *a , char *b)
{
    while(*a != '\0' && *b != '\0')
    {
        if(*a > *b) return 1;
        if(*b > *a) return -1;
        a++ , b++;
    }
    return 0;
}

int main(void) 
{
    char a[4040], b[2020];
    scanf("%s", a);
    scanf("%s", b);
    printf("%d" ,  Mystrcmp(a, b) );
    return 0;
}