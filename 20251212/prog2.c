#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/*
Sa se decleare o structura adecvata pentru a stoca
informatii despre animale.Un animal este careacterizat
prin nume,greutate, clasa

Sa se citeasca de la tastatura informatii despre un numar necunoscut
de animale si sa se afiseze numele primelor doua animale in oridene alfabetica
Nu este nevoie de Sortare
*/

typedef struct Animals 
{
    char name[30];
    float weight;
    char class[20];
} Animal;

int main()
{
    // citire numar necunoscut de numere
    int n = 0;
    Animal *v = NULL;
    Animal *v2;
    for (;;)
    {
        Animal a;
        printf("Animal %d\n", n + 1);
        printf("Nume: ");
        if (scanf("%29s", a.name) != 1)
        {
            break;
        }
        printf("Greutate: ");
        if (scanf("%f", &a.weight) != 1)
        {
            break;
        }
        printf("Clasa: ");
        if (scanf("%19s", a.class) != 1)
        {
            break;
        }
        n++;
        if((v2=(Animal*)realloc(v,n*sizeof(Animal))) == NULL)
        {
            printf("memorie insuficienta\n");
            free(v);
            exit(EXIT_FAILURE);
        }
        v = v2;
        v[n-1] = a;
    }

    if (n >= 2) 
    {
        Animal first, second;
        if (strcmp(v[0].name, v[1].name) < 0) 
        {
            first = v[0];
            second = v[1];
        } 
        else 
        {
            first = v[1];
            second = v[0];
        }
        printf("Primele doua animale in ordine alfabetica:\n");
        printf("1. %s\n", first.name);
        printf("2. %s\n", second.name);
    } 
    else 
    {
        printf("Nu sunt suficiente animale pentru afisare.\n");
    }

    free(v);
}