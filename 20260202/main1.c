#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t resetBits(uint64_t x, uint8_t p, uint8_t n)
{
    if ((p + n) > 64)
    {
        perror(NULL);
        return 0;
    }
    for (uint32_t cnt = p; cnt < p + n; cnt++)
    {
        x &= ~(1ULL << cnt);
    }
    return x;
}

void Show_Bits(uint64_t Input)
{
    uint64_t mask;
    for (uint32_t i = 0; i < 64; i++)
    {
        mask = 1ULL << i;
        if (Input & mask)
        {
            printf("%d", 1);
        }
        else
        {
            printf("%d", 0);
        }
    }
    printf("\n");
}

int main()
{
    uint64_t Input;
    uint8_t Start_Poz;
    uint8_t Number_Of_Resets;
    printf("Introduceti Input : ");
    if(scanf("%lu", &Input) !=1)
    {
        perror(NULL);
        exit(1);
    }
    printf("Introduceti pozitia de start reset : ");
    if(scanf("%hhu", &Start_Poz) != 1)
    {
        perror(NULL);
        exit(1);
    }
    printf("Introduceti nr de biti resetati : ");
    if(scanf("%hhu", &Number_Of_Resets) != 1)
    {
        perror(NULL);
        exit(1);
    }
    uint64_t Output = resetBits(Input, Start_Poz, Number_Of_Resets);
    Show_Bits(Output);
    return 0;
}