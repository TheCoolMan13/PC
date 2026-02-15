#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define CHUNK 1024

typedef struct
{
    uint16_t AN;
    char NUME[30];
    uint16_t APARITII;
    uint16_t POZITIE;
} Linie_An;

int INDEX_GLOBAL = 0;

Linie_An *To_Table(char *Line, Linie_An *TABLOU_VAR)
{
    static int INDEX_CURENT = 0;
    static int INDEX_MAXIM = CHUNK;
    if (TABLOU_VAR == NULL)
    {
        TABLOU_VAR = malloc(CHUNK * sizeof(Linie_An));
    }
    if (INDEX_CURENT + 1 > INDEX_MAXIM)
    {
        printf("INCERCARE REALLOCARE \n\n\n\n\n");
        INDEX_MAXIM = INDEX_CURENT + CHUNK;
        printf("%d\n", INDEX_MAXIM);
        TABLOU_VAR = realloc(TABLOU_VAR, INDEX_MAXIM * sizeof(Linie_An));
    }

    char *cursor = strtok(Line, ",");
    uint16_t an_citit = atoi(cursor);
    cursor = strtok(NULL, ","); // sarim peste sex
    cursor = strtok(NULL, ",");
    char *nume_citit = cursor;
    cursor = strtok(NULL, ",");
    uint16_t aparitii_citite = atoi(cursor);
    cursor = strtok(NULL, ",");
    uint16_t pozitie_citita = atoi(cursor);

    printf("%d %s %d %d \n", an_citit, nume_citit, aparitii_citite, pozitie_citita);
    TABLOU_VAR[INDEX_CURENT].AN = an_citit;
    strcpy(TABLOU_VAR[INDEX_CURENT].NUME, nume_citit);
    TABLOU_VAR[INDEX_CURENT].APARITII = aparitii_citite;
    TABLOU_VAR[INDEX_CURENT].POZITIE = pozitie_citita;
    INDEX_CURENT++;
    INDEX_GLOBAL = INDEX_CURENT;
    return TABLOU_VAR;
}
int total_extreme = 0;
Linie_An *To_Sort(Linie_An *TABLOU_VAR)
{
    int INDEX_EXTREME = 0;
    int INDEX_MAXIM = CHUNK;
    Linie_An *Tablou_Sortat = malloc(CHUNK * sizeof(Linie_An));

    for (int i = 0; i < INDEX_GLOBAL; i++)
    {
        // Dacă suntem la prima linie dintr-un an (Cel mai comun)
        // SAU dacă suntem la ultima linie dintr-un an (Cel mai puțin comun)
        // Verificăm dacă anul se schimbă față de rândul anterior sau următor

        int este_primul = (i == 0 || TABLOU_VAR[i].AN != TABLOU_VAR[i - 1].AN);
        int este_ultimul = (i == INDEX_GLOBAL - 1 || TABLOU_VAR[i].AN != TABLOU_VAR[i + 1].AN);

        if (este_primul || este_ultimul)
        {
            if (INDEX_EXTREME >= INDEX_MAXIM)
            {
                INDEX_MAXIM += CHUNK;
                Tablou_Sortat = realloc(Tablou_Sortat, INDEX_MAXIM * sizeof(Linie_An));
            }
            Tablou_Sortat[INDEX_EXTREME] = TABLOU_VAR[i];
            INDEX_EXTREME++;
        }
    }
    total_extreme = INDEX_EXTREME; // Salvăm câte am găsit
    return Tablou_Sortat;
}

void SCRIERE_IN_OUTPUT(Linie_An *Tablou, FILE *output)
{
    for (int i = 0; i < total_extreme; i++)
    {
        fprintf(output, "%d,%s,%d,%d\n",
                Tablou[i].AN, Tablou[i].NUME,
                Tablou[i].APARITII, Tablou[i].POZITIE);
    }
}

int main()
{
    FILE *input = NULL;
    FILE *output = NULL;
    const char *inputName = "babies-first-names-all-names-all-years.csv";
    const char *outputName = "babies.csv";

    if ((input = fopen(inputName, "r")) == NULL)
    {
        perror(NULL);
        exit(1);
    }
    if ((output = fopen(outputName, "w")) == NULL)
    {
        perror(NULL);
        fclose(input);
        exit(1);
    }

    char ReadLine[128];
    fgets(ReadLine, 128, input);
    Linie_An *TABLOU_VAR = NULL;
    while (fgets(ReadLine, 128, input) != NULL)
    {
        // printf("%s", ReadLine);
        // fputs(ReadLine, output);
        TABLOU_VAR = To_Table(ReadLine, TABLOU_VAR);
    }

    printf("\n INDEX GLOBAL : %d", INDEX_GLOBAL);
    Linie_An *Tablou_Sortat = NULL;
    Tablou_Sortat = To_Sort(TABLOU_VAR);
    SCRIERE_IN_OUTPUT(Tablou_Sortat, output);
    free(TABLOU_VAR);
    free(Tablou_Sortat);
    fclose(input);
    fclose(output);
    return 0;
}