/*
Tipuri de date complexe
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum zile_saptamana
{
    luni = 5,
    marti,
    miercuri,
    joi,
    vineri,
    sambata,
    duminica
};

int main (void) 
{
enum zile_saptamana zile;
zile = luni;
if(zile == luni)
{
    printf ("azi e luni");
}
printf ("%d\n", zile);
return 0;

}