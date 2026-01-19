#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct mystruct
{
    uint32_t a;
    uint8_t b;
    uint16_t c;
    char t[100];

}MY_STR_TYPE;

MY_STR_TYPE D1;
struct MYSTRUCT2;

typedef enum value
{
    tagD,
    tabB,
}MY_ENUM;
MY_STR_TYPE e;
enum value f;

typedef int MyInt;
MyInt g;

