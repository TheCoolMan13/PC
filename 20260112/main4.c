#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct 
{
    uint16_t x;
    uint8_t aabb[2];
    uint16_t y;
    uint8_t dead[2];
}DATA;

int main(int argc , char **argv)
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        exit(-1);
    }

    FILE *in  = NULL;
    FILE *out = NULL;
    if((in = fopen(argv[1], "r")) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    if((out = fopen(argv[2], "wb")) == NULL)
    {
        perror(argv[2]);
        exit(1);
    }

    uint16_t x, y;
    uint8_t temp;
    DATA d;
    d.aabb[0] = 0xAA;
    d.aabb[1] = 0xBB;
    d.dead[0] = 0xDE;
    d.dead[1] = 0xAD;

    while(fscanf(in, "%hd.%hd", &x, &y) == 2)
    {
      //  printf("Numerele citite sunt: %04X %04X\n", x, y);
        fwrite(&d, sizeof(DATA), 1, out);
    }


    if(fclose(in) < 0)
    {
        perror("fclose input");
        exit(-1);
    }
    if(fclose(out) < 0)
    {
        perror("fclose output");
        exit(-1);
    }

    return 0;
}