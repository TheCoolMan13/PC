#include <stdio.h>

void myStrCpy(char *s, char *p)
{
    while (*s != '\0')
    {
        *p = *s;
        p++, s++;
    }
    *p = '\0';
}
int main(void)
{
    char a[2020], b[2020];
    scanf("%s", a);
    myStrCpy(a, b);
    printf("%s", b);
    return 0;
}