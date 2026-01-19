#include <stdio.h>
#include <string.h>
void MyStrCat(char *s, char *p)
{
    int aux = strlen(s);
    while (*p != '\n')
    {
        *(s + aux) = *p;
        s++,p++;
    }
    *p = '\0';
}

int main(void)
{
    char a[4040], b[2020];
    scanf("%2020s", a);
    scanf("%s", b);
    MyStrCat(a, b);
    printf("%s", a);
    return 0;
}