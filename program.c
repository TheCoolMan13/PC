
/*


se da un numar in baza 10. Sa se calculeze cate cifre are, cate cifre impare are, apoi intr-un numar pe 8 biti
sa se scrie in nibble-ul cel mai nesemnificativ numarul de cifre si pe nibble-ul cel mai semnificativ numarul de
cifre impare.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int CalculCifre(int *NrCifre, int *NrCifrePare, int base10)
{
    while (base10 != 0)
    {
        int cifra = base10 % 10;
        (*NrCifre)++;
        if (cifra % 2 == 0)
        {
            (*NrCifrePare)++;
        }
        base10 /= 10;
    }
    return 0;
}

uint8_t ToBinary(int n)
{
    uint8_t binary = 0;
    int remainder, power = 0;
    while (n > 0)
    {
        remainder = n % 2;

        if (remainder == 1)
        {
            binary |= 1 << power;
        }
        n /= 2;
        power++;
    }
    return binary;
}

void print_bit_8(uint8_t nr)
{
    uint8_t mask = 1UL << 7; // 0b1000000000000000
    uint8_t i = 0;
    for (i = 0; i < 8; i++)
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

int main(void)
{

    /////////////////// PARTEA 1 ///////////////////

    int base10;
    if (scanf("%d", &base10) == 0)
    {
        return 0;
    }
    int NrCifre = 0, NrCifrePare = 0;
    CalculCifre(&NrCifre, &NrCifrePare, base10);
    printf("Numarul de cifre este: %d\n", NrCifre);
    printf("Numarul de cifre pare este: %d\n", NrCifrePare);

    ////////////////// PARTEA 2 ///////////////////

    uint8_t NrCifreBin = ToBinary(NrCifre);
    uint8_t NrCifrePareBin = ToBinary(NrCifrePare);

    uint8_t rezultat = NrCifreBin | (NrCifrePareBin << 4);
    print_bit_8(rezultat);
    printf("\n");
    
    uint8_t rezultat2 = (NrCifrePare << 4) | NrCifre;
    print_bit_8(rezultat2);

    /*
    1234

    NrCifre = 4
    NrCifrePare = 2

    NrCifreBin = 0000 0100
    NrCifrePareBin = 0000 0010

    rezultat = 0010 0100

    */

    return 0;
}