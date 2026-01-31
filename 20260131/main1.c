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
        fclose(input);
        exit(1);
    }

    uint32_t BUFFER[BUFFER_SIZE];
    uint32_t Read_Numbers;
    while((Read_Numbers = fread(BUFFER, sizeof(uint32_t) , BUFFER_SIZE, input) )>0)
    {
        for(int i = 0 ; i<Read_Numbers; i++)
        {
            if(fprintf(output , "%08X\n" , *(BUFFER+i)) < 0)
            {
                perror(NULL);
                fclose(input);
                fclose(output);
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