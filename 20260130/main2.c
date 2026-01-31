#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/*

Se citesc de la tastatură maxim 100 numere reale,
până la întâlnirea numărului 0. Să se sorteze aceste
numere și să se scrie într-un fișier, toate numerele
fiind pe o singură linie, separate prin | (bară verticală).
*/

int compare(const void *a, const void *b)
{
    return *(uint16_t *)a - *(uint16_t *)b;
}

int main()
{
    FILE *output;
    char *outputname = "output2.txt";

    if ((output = fopen(outputname, "w")) == NULL)
    {
        fprintf(stderr, "Eroare deschidere output");
        exit(1);
    }

    uint16_t ReadNumber, NumberIndex = 0;
    uint16_t NumberArr[101] = {0};

    while ((scanf("%hu", &ReadNumber) == 1) && ReadNumber != 0)
    {
        NumberArr[NumberIndex] = ReadNumber;
        NumberIndex++;
    }
    qsort(NumberArr, NumberIndex, sizeof(uint16_t), compare);
    for (int i = 0; i < NumberIndex; i++)
    {
        fprintf(output, "%hu | ", *(NumberArr + i));
    }

    return 0;
}