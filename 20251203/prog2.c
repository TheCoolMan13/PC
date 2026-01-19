#include <stdio.h>
#include <stdlib.h>
#define MAX_SENZORI 100

struct senzori
{
    char nume[50];
    char nr_serie[30];
    enum tip_senzor
    {
        TEMPERATURA,
        UMIDITATE,
        PRESIUNE
    } tip;
    float valoare;
    float valoare_critica;
};

int citire_senzori(struct senzori *senzori_array, int count)
{

    for (int i = 0; i < count; i++)
    {
        printf("Daca vreti sa opriti introducerea senzorilor, tastati 0. Pentru a continua, tastati 1: ");
        int optiune;
        scanf("%d", &optiune);
        if (optiune == 0)
        {
            return i;
        }
        printf("Introduceti numele senzorului %d: ", i + 1);
        scanf("%49s", senzori_array[i].nume);
        printf("Introduceti numarul de serie al senzorului %d: ", i + 1);
        scanf("%29s", senzori_array[i].nr_serie);
        int tip_input;
        printf("Introduceti tipul senzorului %d (0 - TEMPERATURA, 1 - UMIDITATE, 2 - PRESIUNE): ", i + 1);
        scanf("%d", &tip_input);
        senzori_array[i].tip = (enum tip_senzor)tip_input;
        printf("Introduceti valoarea senzorului %d: ", i + 1);
        scanf("%f", &senzori_array[i].valoare);
    }
    return count;
}

void afisare_senzori(const struct senzori *senzori_array, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Senzor %d: Nume = %s, Nr Serie = %s, Valoare = %.2f",
               i + 1,
               senzori_array[i].nume,
               senzori_array[i].nr_serie,
               senzori_array[i].valoare);

        switch (senzori_array[i].tip)
        {
        case TEMPERATURA:
            printf("Tip: TEMPERATURA\n");
            break;
        case UMIDITATE:
            printf("Tip: UMIDITATE\n");
            break;
        case PRESIUNE:
            printf("Tip: PRESIUNE\n");
            break;
        default:
            printf("Tip: Necunoscut\n");
            break;
        }
    }
}

void afisare_senzor_singular(const struct senzori *senzor)
{
    printf("Senzor: Nume = %s, Nr Serie = %s, Tip = %d, Valoare = %.2f\n",
           senzor->nume,
           senzor->nr_serie,
           senzor->tip,
           senzor->valoare);
}

void alerta_senzor(const struct senzori *senzor)
{
    if (senzor->valoare > senzor->valoare_critica)
    {
        printf("ALERTA: Senzorul %s a depasit valoarea critica!\n", senzor->nume);
    }
}

int main(void)
{
    struct senzori senzori_array[MAX_SENZORI];
    int count = citire_senzori(senzori_array, MAX_SENZORI);
    printf("\nSenzorii introdusi sunt:\n");
    afisare_senzori(senzori_array, count);
    for (int i = 0; i < count; i++)
    {
        printf("Introduceti valoarea critica pentru senzorul %s: ", senzori_array[i].nume);
        scanf("%f", &senzori_array[i].valoare_critica);
        alerta_senzor(&senzori_array[i]);
    }
    alerta_senzor(&senzori_array[0]);
    return 0;
}