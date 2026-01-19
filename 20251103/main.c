#include <stdio.h>
#include <stdint.h>

void print_bit_16(uint16_t nr)
{
    uint16_t mask = 0x8000; // 0b1000000000000000
    uint8_t i = 0;
    for (i = 0; i < 16; i++)
    {
        if ((nr & mask) == 0)
        {
            printf("0");
        }
        else
        {
            printf("1");
        }
        mask = mask >> 1; // mask >>= 1;
    }
    printf("\n");
}

uint16_t InversareNibble(int nr)
{
    uint16_t mask1 = 0x000F; // 0b0000000000001111
    uint16_t mask2 = 0x00F0; // 0b0000000011110000
    uint16_t mask3 = 0x0F00; // 0b0000111100000000
    uint16_t mask4 = 0xF000; // 0b1111000000000000

    uint16_t nibble1 = ((uint16_t)nr & mask1) << 12;
    uint16_t nibble2 = ((uint16_t)nr & mask2) << 4;
    uint16_t nibble3 = ((uint16_t)nr & mask3) >> 4;
    uint16_t nibble4 = ((uint16_t)nr & mask4) >> 12;

    return (nibble1 | nibble2 | nibble3 | nibble4);
}

int main(void)
{
   int Number;
   if(scanf("%d", &Number) != 1) {
       printf("Invalid input\n");
       return 1;
    }
    uint16_t result = InversareNibble(Number);
    printf("Result after nibble inversion: 0x%04X\n", result);
    print_bit_16(result);
    /*
    Test value: 305419896 (0x12345678)
    Expected output: 0x56781234
    1111000011100000
    1111 0000 1110 0000
    0001 0110 1111 1100
    */
    return 0;
}
