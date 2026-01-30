/*

8. Să se scrie o funcție ca primește ca parametru o propoziție și returnează un string alocat dinamic ce reprezintă propoziția citită translatată în "limba păsărească". Translatarea în "păsărească" constă în faptul că fiecare vocală întâlnită se dublează punându-se și caracterul 'p' înaintea vocalei dublate. Practic vocalele se tranformă astfel:

a -> apa
e -> epe
i -> ipi
o -> opo
u -> upu

Exemplu: ana are mere și apa-> apanapa aparepe meperepe sipi apapapa.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define CHUNK 100

char *human2pasa(const char *input)
{
    if (input == NULL)
        return NULL;
    char *output = malloc(strlen(input) * sizeof(char));
    if (!output)
        return NULL;

    uint32_t IndexOutput = 0;
    char *IndexCurent = output;
    char *IndexLimit = output + (strlen(input) * sizeof(char));

    for (int i = 0; i < strlen(input); i++)
    {
        IndexCurent = IndexOutput + output;
        if (IndexCurent + 4 >= IndexLimit)
        {
            if ((output = realloc(output, (IndexLimit - output) + CHUNK)) == NULL)
            {
                perror(NULL);
                exit(1);
            }
            IndexCurent = IndexOutput + output;
            IndexLimit = output + IndexOutput + CHUNK;
        }

        if (input[i] == 'a' || input[i] == 'e' || input[i] == 'i' || input[i] == 'o' || input[i] == 'u')
        {
            *(output + IndexOutput) = *(input + i);
            *(output + IndexOutput + 1) = 'p';
            *(output + IndexOutput + 2) = *(input + i);
            IndexOutput += 3;
        }
        else
        {
            *(output + IndexOutput) = *(input + i);
            IndexOutput++;
        }
    }
    output[IndexOutput] = '\0';
    return output;
}

int main(int argv, char **argc)
{

    if (argv != 3)
    {
        fprintf(stderr, "Eroare argumente");
        exit(1);
    }

    FILE *input;
    if ((input = fopen(argc[1], "r")) == NULL)
    {
        perror(NULL);
        exit(-1);
    }

    FILE *output;
    if ((output = fopen(argc[2], "w")) == NULL)
    {
        perror(NULL);
        exit(-1);
    }

    char cuvant[128];
    while (fgets(cuvant, 128, input) != NULL)
    {
        cuvant[strcspn(cuvant, "\n\r")] = '\0';

        // printf("CUVANT : %s \n", cuvant);

        char *decoded = human2pasa(cuvant);
        if (fwrite(decoded, sizeof(char), strlen(decoded), output) != strlen(decoded))
        {
            free(decoded);
            perror(NULL);
            exit(-1);
        }
        free(decoded);
    }

    if (fclose(input) != 0)
    {
        perror(NULL);
        exit(-1);
    }

    if (fclose(output) != 0)
    {
        perror(NULL);
        exit(-1);
    }
    return 0;
}