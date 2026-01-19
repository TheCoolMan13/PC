#include <stdio.h>
#include <stdint.h>

uint8_t PartitateBit8(uint8_t nr)
{
    int i = 0;
    int count = 0;
    uint8_t m = 0x80;
    for (i = 0; i < 8; i++)
    {
        if (nr & m)
        {
            printf("1");
            count++;
        }
        else
            printf("0");
        m >>= 1;
    }
    if (count % 2 == 0)
        return 1;
    return 0;
}

void printBit8(uint8_t nr)
{
    int i = 0;
    uint8_t m = 0x80;
    for (i = 0; i < 8; i++)
    {
        if (nr & m)
            printf("1");
        else
            printf("0");
        m >>= 1;
    }
}

int main()
{

    uint8_t number = 13; // Example number
    uint8_t nr;
    printf("Binary representation of %d is: ", number);
    printBit8(number);
   // scanf("%hhc" , &nr);
    if(!scanf("%hhc", &nr)) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("%hhx parity bit is: ",PartitateBit8(nr));
    printf("\n");
    return 0;
}