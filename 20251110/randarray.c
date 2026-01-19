#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000


int read_array_random(uint32_t *a, int size)
{
    int i = 0;
    for(i = 0; i < size; i++)
    {
        if(scanf("%u", &a[i]) != 1)
        {
            break;
        }
    }
    return i;
}
void print_array(uint32_t *a, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%u\n", a[i]);
    }
}

int main(void)
{
    uint32_t arr[MAX];
    // srand(time(NULL));
    // for (int i = 0; i < 10; i++)
    // {
    //     arr[i] = rand() % MAX; 
    // }

    // for(int i = 0 ; i <10 ; i++) 
    // {
    //     printf("%d\n" , arr[i]);
    // }


    int s = read_array_random(arr, MAX);
    print_array(arr, s);

    return 0;
}