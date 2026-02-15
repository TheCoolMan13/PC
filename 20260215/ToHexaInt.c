#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CHUNK 1024

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "EROARE ARGUMENTE");
        exit(1);
    }
    FILE *input = NULL;
    FILE *output = NULL;

    if ((input = fopen(argv[1], "rb")) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    if ((output = fopen(argv[2], "w")) == NULL)
    {
        perror(argv[2]);
        fclose(input);
        exit(1);
    }

    // 4 bytes -- > hexa cate 8 cifre hexa / rand
    // prima chestie vreau sa citesc tot si sa rescriu in output exact asa cum e

    uint32_t buffer;

    while (fread(&buffer, sizeof(uint32_t), 1, input) == 1)
    {
        fprintf(output, "%08X\n", buffer);
        // printf("%08X \n", buffer);
    }

    if (fclose(input) != 0)
    {
        perror(NULL);
        fclose(output);
        exit(1);
    }
    if (fclose(output) != 0)
    {
        perror(NULL);
        exit(1);
    }

    return 0;
}