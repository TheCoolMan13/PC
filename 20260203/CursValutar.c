// pagina 33 Problema cu curs valutar
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INDEX_CHUNK 1024

typedef struct
{
    float VALUE;
    uint16_t YEAR;
    uint16_t MONTH;
    uint16_t DAY;
} CURS;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        perror(NULL);
        exit(1);
    }
    FILE *input;
    FILE *output;
    if ((input = fopen(argv[1], "r")) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    if ((output = fopen(argv[2], "w")) == NULL)
    {
        perror(argv[2]);
        exit(1);
    }

    char line[64];
    uint32_t IndexCursuri = 0;
    uint32_t IndexCursuriMaxim = INDEX_CHUNK;
    // printf("%ld", sizeof(CURS));
    CURS *Lista_Cursuri = malloc(INDEX_CHUNK * sizeof(CURS));

    while (fgets(line, sizeof(line), input) != NULL)
    {
        float value = atof(line + 11);
        // printf("%f ESTE VALUE", value);
        line[10] = '\0';

        uint16_t year = atoi(line + 6);
        // printf("%u ESTE YEAR", year);
        line[5] = '\0';

        uint16_t month = atoi(line + 3);
        // printf("%u ESTE MONTH", month);
        line[2] = '\0';

        uint16_t day = atoi(line);
        // printf("%u ESTE DAY", day);

        if (IndexCursuri + 2 > IndexCursuriMaxim)
        {
            if ((Lista_Cursuri = realloc(Lista_Cursuri, (IndexCursuri + INDEX_CHUNK) * sizeof(CURS))) == NULL)
            {
                perror(NULL);
                fclose(input);
                fclose(output);
                exit(1);
            }
            IndexCursuriMaxim = IndexCursuri + INDEX_CHUNK;
        }
        Lista_Cursuri[IndexCursuri].VALUE = value;
        Lista_Cursuri[IndexCursuri].YEAR = year;
        Lista_Cursuri[IndexCursuri].MONTH = month;
        Lista_Cursuri[IndexCursuri].DAY = day;
        IndexCursuri++;
        // if (fprintf(output, "%u.%u.%u VALUE : %f \n", Lista_Cursuri[IndexCursuri].DAY, Lista_Cursuri[IndexCursuri].MONTH, Lista_Cursuri[IndexCursuri].YEAR, Lista_Cursuri[IndexCursuri].VALUE) < 0)
        // {
        //     perror(NULL);
        //     fclose(input);
        //     fclose(output);
        //     exit(1);
        // }
    }

    // Presupunem ca anii sunt ordonati deja descrescator daca nu mergeam prin tot tabloul cu un for si gata
    uint16_t TargetedYear = Lista_Cursuri[0].YEAR;
    uint16_t MaxValue = 0;
    uint16_t IndexForMaxValue = 0;
    for (uint32_t Cursor = 0; Cursor < IndexCursuri; Cursor++)
    {
        if (TargetedYear != Lista_Cursuri[Cursor].YEAR)
        {
            // Cazul de printare
            if (fprintf(output, "%u.%u.%u,%f \n", Lista_Cursuri[IndexForMaxValue].DAY, Lista_Cursuri[IndexForMaxValue].MONTH, Lista_Cursuri[IndexForMaxValue].YEAR, Lista_Cursuri[IndexForMaxValue].VALUE) < 0)
            {
                perror(NULL);
                fclose(input);
                fclose(output);
                exit(1);
            }
            MaxValue = 0;
            IndexForMaxValue = 0;
            TargetedYear = Lista_Cursuri[Cursor].YEAR;
            continue;
        }
        if (Lista_Cursuri[Cursor].VALUE > MaxValue)
        {
            IndexForMaxValue = Cursor;
            MaxValue = Lista_Cursuri[Cursor].VALUE;
        }
    }
    if (fclose(input) != 0)
    {
        perror(NULL);
        exit(1);
    }
    if (fclose(output) != 0)
    {
        perror(NULL);
        exit(1);
    }
    return 0;
}