#include <stdio.h>
#include <stdlib.h>
/*
Se citesc numere până la întâlnirea numărului 0.
Să se afișeze aceste numere în ordine inversă.
Programul va folosi doar minimul necesar de memorie
*/

int main()
{
    int numar;
    int *arr = NULL;
    int size = 0;
    while ((scanf("%d", &numar)) == 1 && numar != 0)
    {
        if ((arr = (int *)realloc(arr, (size + 1) * sizeof(int))) == NULL)
        {
            perror(NULL);
            exit(-1);
        }
        *(arr + size) = numar;
        size++;
    }
    for (int i = size - 1; i >= 0; i--)
    {
        printf("%d ", *(arr + i));
    }
    free(arr);
    return 0;
}