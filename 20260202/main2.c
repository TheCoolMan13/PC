//pagina 15
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void Show_Bits(uint64_t Input)
{
    uint64_t mask;
    for(uint32_t i = 0 ; i < 64 ; i++)
    {
        mask = 1ULL << i;
        if(Input & mask)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

uint64_t RotateBits(uint64_t Input)
{
    uint64_t Output = Input >> 1;
    uint64_t aux = Input & 1ULL;
    Output |= aux << 63;
    return Output;
}

int main(int argc , char **argv)
{
    if(argc != 3)
    {
        fprintf(stderr , "EROARE ARGUMENTE");
        exit(-1);
    }
    uint64_t InputNumber = strtoull(argv[1], NULL, 10);
    uint16_t NumRotations = (uint16_t)atoi(argv[2]);
    // printf("%lu " , InputNumber);
    // printf("%hu" , NumRotations);

    if(NumRotations > 64)
    {
        fprintf(stderr , "NUM ROTATIONS TOO HIGH");
        exit(1);
    }
    Show_Bits(InputNumber);
    uint64_t Output = InputNumber;
    printf("\n");
    for(uint16_t cnt = 0 ; cnt < NumRotations ; cnt++)
    {
        Output = RotateBits(Output);
    }
    Show_Bits(Output);
    return 0;
}