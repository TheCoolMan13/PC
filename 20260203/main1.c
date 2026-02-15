#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint16_t a;
    uint32_t b;
} STRUCT;
int main()
{
    printf("%ld", sizeof(STRUCT));
}