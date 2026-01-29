#include <stdio.h>
#include <stdint.h>

/*
: Se citește un număr n (n<=10) și apoi n numere întregi.
Se cere să se sorteze aceste numere în ordine descrescătoare
utilizând pointeri, fără indecși. (Inclusiv citirea se va face
cu pointeri.)
*/

int main()
{
    int arr[10];
    int size;
    int *n = arr;
    if (scanf("%d", &size) != 1)
    {
        printf("Error reading input\n");
        return 1; // Error reading input
    }
    if (size > 10 || size < 0)
    {
        printf("Numar invalid\n");
        return 1; // Invalid number
    }

    for (int i = 0; i < size; i++)
    {
        if (scanf("%d", n + i) != 1)
        {
            printf("Error reading input\n");
            return 1; // Error reading input
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (*(n + i) > *(n + j))
            {
                int aux = *(n + i);
                *(n + i) = *(n + j);
                *(n + j) = aux;
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *(n + i));
    }
    return 0;
}