/*
O structură conține ora (ca și o altă structură potrivită) la care s-a măsurat o anumită
 temperatură și valoarea acestei temperaturi (real). Se cere n<=10 și apoi n temperaturi
 cu ora la care au fost măsurate. Se cere apoi o oră de început și una de sfârșit.
 Să se afișeze media temperaturilor care au fost măsurate în acel interval orar, inclusiv
 în capetele acestuia.

*/

#include <stdio.h>

typedef struct
{
    int temperatura;
    int ora;
} senzor;

int main()
{
    int n;
    senzor sera[11];
    if (scanf("%d", &n) == 0)
    {
        printf("EROARE CITIRE");
        return -1;
    }
    for (int i = 0; i < n; i++)
    {
        printf("Introduceti temperatura sera %d :", i);
        scanf("%d", &sera[i].temperatura);
        printf("Introduceti ora sera %d :", i);
        scanf("%d", &sera[i].ora);
    }
    float media;
    for (int i = 0; i < n; i++)
    {
        media += sera[i].temperatura;
    }
    media /= n;
    printf("\n Media temp este:", media);
    return 0;
}