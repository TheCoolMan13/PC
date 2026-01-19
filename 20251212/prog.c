#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    // citire numar necunoscut de numere
    int n = 0;
    int *v = NULL;
    int *v2;
    for (;;)
    {
        int k;
        printf("v[%d]=", n);
        if (scanf("%d", &k) != 1)
        {
            break;
        }
        n++;
        if((v2=(int*)realloc(v,n*sizeof(int))) == NULL)
        {
            printf("memorie insuficienta\n");
            free(v);
            exit(EXIT_FAILURE);
        }
        v = v2;
        v[n-1] = k;
    }
    for (int i = 0; i < n; i++) printf("%d\n", v[i]);
    free(v);
}