/*
Se considera un fisier binar ce contine numere intregi pe 4 bytes. Programul nu va cunoaste dimensiunea fisierului. Sa se scrie un program format din mai multe functii: o functie ce citeste un astfel de fisier si stocheaza numerele intr-un tablou. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// Folosec tot integers.bin 

#define BUFFER_SIZE 100


void Adaugare_In_Tablou(uint32_t **NumberArray ,uint32_t *NumberArraySize, uint32_t *BUFFER , uint32_t Read_Numbers)
{
    *NumberArray = realloc(*NumberArray, (*NumberArraySize + Read_Numbers) * sizeof(uint32_t));
    
    if(!(*NumberArray))
    {
        perror(NULL);
        exit(1);
    }

    for(int i = 0 ; i < Read_Numbers ; i++)
    {
      (*NumberArray)[*NumberArraySize + i] = *(BUFFER + i);
    }
    *NumberArraySize += Read_Numbers;
}

int Compare_Sort(const void *a , const void *b)
{
    uint32_t val1 = *(uint32_t *)a;
    uint32_t val2 = *(uint32_t *)b;
    if (val1 < val2) return -1;
    if (val1 > val2) return 1;
    return 0;
}

int main()
{
    char *filename = "integers.bin";
    char *outputname = "int.txt";
    FILE *input = NULL;
    FILE *output = NULL;
    if(( input = fopen(filename , "rb")) == NULL)
    {
        perror(NULL);
        exit(1);
    }
    if(( output = fopen(outputname , "w")) == NULL)
    {
        perror(NULL);
        fclose(input);
        exit(1);
    }

    uint32_t BUFFER[BUFFER_SIZE + 1];
    uint32_t Read_Numbers, NumberArraySize = 0;
    uint32_t *NumberArray = NULL;
    while((Read_Numbers = fread(BUFFER, sizeof(uint32_t) , BUFFER_SIZE, input) )>0)
    {
        Adaugare_In_Tablou(&NumberArray, &NumberArraySize , BUFFER, Read_Numbers);
    }

    qsort(NumberArray , NumberArraySize, sizeof(uint32_t), Compare_Sort);

    for(int i = 0 ; i < NumberArraySize ; i++)
    {
        printf("%u " , *(NumberArray + i) );
    }
    
    if(NumberArray)
    free(NumberArray);
    if(fclose(input) != 0)
    {
        perror(NULL);
        exit(1);
    }
    if(fclose(output) !=0)
    {
        perror(NULL);
        exit(1);
    }
    return 0;
}