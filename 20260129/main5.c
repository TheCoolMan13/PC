#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
/*
Se va citi de la intrarea standard un numar neconscut de valor
 intregi nenule pozitive pana la EOF. Se vor stoca aceste
 elemente intr-un tablou dinamic. Programul va afisa la
 iesirea standard tabloul sortat descrescator.
*/

#define CHUNK 100 // Allocam cate 100 de CHUNK uri

int compare(const void *a, const void *b)
{
    return (*(uint16_t *)b - *(uint16_t *)a);
}

int main()
{

    uint16_t Input_number;
    uint16_t *Number_arr = (uint16_t *)malloc(CHUNK * sizeof(uint16_t));
    if (!Number_arr)
    {
        perror(NULL);
        exit(-1);
    }
    uint16_t *IndexCurr = Number_arr;
    uint16_t *IndexLimit = Number_arr + CHUNK;

    while (scanf("%hu", &Input_number) == 1)
    {
        if (IndexCurr == IndexLimit)
        {
            uint16_t ElementeCurente = IndexCurr - Number_arr;
            Number_arr = (uint16_t *)realloc(Number_arr, (ElementeCurente + CHUNK) * sizeof(uint16_t));
            IndexLimit = Number_arr + ElementeCurente + CHUNK;
            IndexCurr = Number_arr + ElementeCurente;
            *IndexCurr++ = Input_number;
        }
        else
        {
            *IndexCurr++ = Input_number;
        }
    }

    uint16_t ElementeTotale = IndexCurr - Number_arr;

    if (ElementeTotale > 0)
    {
        qsort(Number_arr, ElementeTotale, sizeof(uint16_t), compare);

        for (uint16_t *p = Number_arr; p < IndexCurr; p++)
        {
            printf("%hu ", *p);
        }
    }

    free(Number_arr);
    return 0;
}