#include <stdio.h>
#include <stdint.h>

/*
Scrieți o funcție care primește ca și argumente 4 numere întregi pe 1 byte fără semn (n3, n2, n1, n0) și
returnează un număr întreg pe 4 bytes (n) format din cele 4 numere unde n3 este partea cea mai semnificativă și
n0 partea cea mai puțin semnficativă
exemplu: n3 = 1111 0000, n2 = 0011 1100, n1 = 1010 0011, n0 = 0010 1101 -> n = 1111 0000 0011 1100 1010 0011 0010 1101
*/
// 11110000 00111100 10100011 00101101

uint32_t To_Big_Number(uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3)
{
    uint32_t TARGET = 0;
    TARGET |= (uint32_t)n3 << 24;
    TARGET |= (uint32_t)n2 << 16;
    TARGET |= (uint32_t)n1 << 8;
    TARGET |= (uint32_t)n0;
    return TARGET;
}

int main()
{
    uint8_t n0, n1, n2, n3;
    scanf("%hhu%hhu%hhu%hhu", &n3, &n2, &n1, &n0);
    printf("%hhu , %hhu , %hhu , %hhu", n3, n2, n1, n0);
    uint32_t Result = To_Big_Number(n0, n1, n2, n3);
    uint32_t WantedResult = 0b11110000001111001010001100101101;
    if (Result == WantedResult)
    {
        printf("TEST SUCCEDED");
    }
    else
    {
        printf("TEST FAILED");
    }
    printf("\n %u", Result);
    return 0;
}