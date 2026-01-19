#include <stdio.h>
#include <string.h>


struct Studenti
{
    char nume[100];
    int punctaj;
}student[100];


void canstigator(struct Studenti student[], int n)
{
    int max = -1 , poz = -1;
    for(int i = 0 ; i< n ; i++)
    {
        if(student[i].punctaj > max)
        {
            max = student[i].punctaj;
            poz = i;
        }
    }
    printf("%s %d" , student[poz].nume , student[poz].punctaj);
}


int main ()
{

    int n = 3;

    strcpy(student[0].nume, "Ana");
    student[0].punctaj = 85;

    strcpy(student[1].nume, "Ion");
    student[1].punctaj = 92;

    strcpy(student[2].nume, "Maria");
    student[2].punctaj = 78;

    castigator(student, n);
    return 0;
}