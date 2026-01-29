#include <stdio.h>
#include <stdint.h>

/*
Se citesc două variabile, a și b, de tip întreg.
Să se stocheze într-un pointer adresa variabilei care
conține valoarea maximă și apoi să se afișeze valoarea
pointată
*/

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    int *pmax = NULL;
    pmax = (a > b) ? &a : &b;
    printf("%d\n", *pmax);
    return 0;
}