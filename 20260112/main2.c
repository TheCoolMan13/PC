#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 1000

// ./p input_file output_file

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        exit(-1);
    }
    FILE *input = NULL;
    if ((input = fopen(argv[1], "rb")) == NULL)
    {
        perror("fopen input");
        exit(-1);
    }
    FILE *out = NULL;
    if ((out = fopen(argv[2], "wb")) == NULL)
    {
        perror("fopen output");
        exit(-1);
    }
    // man fread

    uint8_t array[SIZE];
    int count_Chars = 0, count_NonChars = 0;
    int r = 0;
    while (r = fread(array, sizeof(uint8_t), SIZE, input) > 0)
    {
        for (int i = 0; i < r; i++)
        {
            if (isprint(array[i]))
            {
                fputc(array[i], out);
                count_Chars++;
            }
            else
            {
                count_NonChars++;
                // printf(".");
            }
        }
    }

    printf("\nNumar caractere: %d\n", count_Chars);
    printf("Numar non-caractere: %d\n", count_NonChars);

    if (fclose(out) < 0)
    {
        perror("fclose output");
        exit(-1);
    }
    if (fclose(input) < 0)
    {
        perror("fclose input");
        exit(-1);
    }
    return 0;
}