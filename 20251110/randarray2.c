#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

int read_array_random(uint32_t *a, int size)
{
    int cnt = 0;
    uint32_t *p = a;
    for (; p < a + size; p++)
    {
        if (scanf("%u", p) != 1)
        {
            break;
        }
        cnt++;
    }
    return cnt;
}
void print_array(const uint32_t *a, int size)
{
    const  uint32_t *p = a;
    for(; p < a + size; p++)
    {
        printf("%u\n", *p);
    }
}

int main(void)
{
    uint32_t arr[MAX];
    int s = read_array_random(arr, MAX);
    print_array(arr, s);

    return 0;
}