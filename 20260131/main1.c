#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE  100
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
        exit(1);
    }

    uint16_t BUFFER[BUFFER_SIZE];
    uint16_t Read_Numbers;
    while((Read_Numbers = fread(BUFFER, sizeof(Read_Numbers) , BUFFER_SIZE, input) )>0)
    {
        for(int i = 0 ; i<Read_Numbers; i++)
        {
            if(fprintf(output , "%08X\n" , *(BUFFER+i)) != 9)
            {
                perror(NULL);
                exit(1);
            }
        }
       
    }
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