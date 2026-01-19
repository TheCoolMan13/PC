#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *text2hex(const char *text)
{
    // text = "abc" -> hex = 0x616263
    char *r = NULL;
    if (r = malloc((strlen(text) * 2 + 1) * sizeof(char)) == NULL)
    {
        return NULL;
    }
    int i = 0;
    char aux[3] = {0};
    int index = 0;
    for (i = 0; i < strlen(text); i++)
    {
        sprintf(r + i * 2, "%02X", (unsigned char)text[i]);
        r[index++] = (unsigned char)aux[0];
        r[index++] = (unsigned char)aux[1];
    }
    r[index] = '\0';
    return r;
}

char *hex2text(const char *hex)
{
    // hex = "0x616263" -> text = "abc"
    char *r = NULL;
    if ((strlen(hex) % 2) != 0)
    {
        return NULL;
    }
    if (strlen(hex) == 0)
    {
        return NULL;
    }
   if(r = malloc((strlen(hex) / 2 +1) * sizeof(char)) == NULL)
    {
        return NULL;
    }
    int i = 0;
    char aux[3];
    aux[2] = '\0';
    char ch;
    for (i = 0; i < strlen(hex) / 2; i = i + 2)
    {
        aux[0] = hex[i];
        aux[1] = hex[i + 1];
        ch = (char)strtol(aux, NULL, 16);
        r[i / 2] = ch;
    }
    r[i / 2] = '\0';
    return r;
}

int main()
{
    const char text[1000];
    if (fgets(text, 1000, stdin) == NULL)
    {
        return 1;
    }
    char *result;
    if ((result = text2hex(text)) != NULL)
    {
        printf("Hexadecimal representation: 0x%s\n", result);
        free(result);
    }

    return 0;
}