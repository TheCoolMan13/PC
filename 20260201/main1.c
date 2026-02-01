#include <stdio.h>
#include <stdint.h>

uint16_t CONFIG_REP(uint64_t LongNumber, uint8_t Target)
{
    printf("NUMBER : %lu TARGET : %hhu", LongNumber, Target);
    Target &= 0xF;
    int cnt = 0;
    for (int i = 0; i <= 60; i++)
    {
        uint8_t current_nibble = (uint8_t)((LongNumber >> i) & 0xF);
        if (current_nibble == Target)
        {
            cnt++;
        }
    }
    return cnt;
}

int main()
{
    uint64_t NUMBER;
    uint8_t TARGET;

    for (;;)
    {
        if (scanf("%lu", &NUMBER) == EOF)
        {
            break;
        }
        if (scanf("%hhu", &TARGET) == EOF)
        {
            break;
        }
        uint16_t REPETITIONS = CONFIG_REP(NUMBER, TARGET);
        printf("\n REPETITIONS :%d ", REPETITIONS);
    }

    return 0;
}