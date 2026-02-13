#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHUNK 1024

int compare(const void *a, const void *b)
{
    uint16_t number1 = *(uint16_t *)a;
    uint16_t number2 = *(uint16_t *)b;
    if (number1 < number2)
        return 1;
    if (number1 > number2)
        return -1;
    return 0;
}

int main(int argc, char **argv)
{
    /*
    ./p3 ANA ARE
    in argc = 3 -> cate argumente sunt dar si ./p3 e argunet
    argv -- martice in care  argv[0] = numele fiserului "main3.c"
    argv[1] ANA
    argv[2] ARE
    argv[1][0] - A
    ./p3 integers.bin output.txt
    */
    if (argc != 3)
    {
        fprintf(stderr, "EROARE ARGUMENTE");
        exit(1);
    }

    FILE *input = NULL;
    FILE *output = NULL;

    if ((input = fopen(argv[1], "rb")) == NULL)
    {
        perror(NULL);
        exit(1);
    }
    if ((output = fopen(argv[2], "w")) == NULL)
    {
        perror(NULL);
        fclose(input);
        exit(1);
    }

    uint32_t IndexCurent = 0;    // Aici tinem minte la ce index suntem in tablou
    uint32_t IndexMaxim = CHUNK; // Indexul maxim pe care il poate tine minte inainte sa crape si trebe realloc
    uint16_t buffer[CHUNK];
    uint16_t NumarElementeCitite;
    uint16_t *Arr = malloc(IndexMaxim * sizeof(uint16_t));
    if (Arr == NULL)
    {
        perror(NULL);
        exit(-1);
    }

    while ((NumarElementeCitite = fread(buffer, sizeof(uint16_t), CHUNK, input)) > 0)
    {

        Arr = realloc(Arr, (IndexMaxim + CHUNK) * sizeof(uint16_t));
        if (Arr == NULL)
        {
            perror(NULL);
            exit(1);
        }
        IndexMaxim += CHUNK;

        for (uint16_t j = 0; j < NumarElementeCitite; j++)
        {
            Arr[IndexCurent + j] = buffer[j];
        }
        IndexCurent += NumarElementeCitite;
    }
    if (IndexCurent == 0)
    {
        perror(NULL);
        exit(-1);
    }
    qsort(Arr, IndexCurent, sizeof(uint16_t), compare);

    for (uint32_t i = 0; i < IndexCurent; i++)
    {
        fprintf(output, "%u\n", Arr[i]);
    }
    free(Arr);
    if (fclose(input) == EOF)
    {
        perror(NULL);
        exit(-1);
    }
    if (fclose(output) == EOF)
    {
        perror(NULL);
        exit(-1);
    }

    return 0;
}