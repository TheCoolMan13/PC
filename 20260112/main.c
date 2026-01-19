/*
ENDIANESS
1) Big Endian - Most Significant Byte first
| 34 | 9B | FD | 7C | | | | |
  a   a+1  a+2  a+3

2) Little Endian - Least Significant Byte first
| 7C | FD | 9B | 34 | | | | |
  a   a+1  a+2  a+3

  mcview - A simple hex viewer
  functia fread() si fwrite() pt fisiere binare

*/

#include <stdio.h>
#include <stdint.h>
#define SIZE 100
int main(int argc, char **argv)
{
    FILE *f;
    uint32_t arg_number;
    if (argc != 3)
    {
        printf("Usage: %s\n", argv[0]);
        return -1;
    }
    arg_number = strtol(argv[2], NULL, 10);

    if ((f = fopen(argv[1], "rb")) == NULL)
    {
        perror(NULL);
        exit(-1);
    }

    // uint32_t nr;
    uint16_t nr;
    int cnt = 0;
    uint16_t array[SIZE];
    int r = 0;
    while (r = fread(array, sizeof(uint16_t), SIZE, f) > 0)
    {
        for(int i = 0; i < r; i++)
        {
            if (array[i] > arg_number)
            {
                printf("Numarul citit este: %04X\n", array[i]);
                cnt++;
            }
        }
    }

    // printf("Numarul citit este: %08X\n", nr);

    fclose(f);
    printf("Au fost gasite %d numere mai mari decat %u\n", cnt, arg_number);
    return 0;
}