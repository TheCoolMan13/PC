#include <stdio.h>  
#include <stdlib.h>
#include <stdint.h>

// mac.txt

int main(int argc , char **argv)
{
    if(argc !=3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }


    FILE *f;
    uint8_t mac[6];
    FILE *o;
    if((f = fopen(argv[1], "r")) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    if ((o = fopen(argv[2], "wb")) == NULL)
    {
        perror(argv[2]);
        exit(1);
    }

    while(fscanf(f, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX\n" , &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]) == 6)
    {
        printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        fwrite(mac, sizeof(uint8_t), 6, o);
    }


    if(fclose(o) <0)
    {
        perror("fclose output");
        exit(1);
    }

    if(fclose(f) <0)
    {
        perror("fclose");
        exit(1);
    }
    return 0;
    //adwdaw
}