#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct
{
    uint8_t len;
    uint8_t data[255];
    uint16_t checksum;
} XBEE;


uint8_t check(const XBEE *xbee)
{
    uint16_t sum = 0;
    for (int i = 0; i < xbee->len; i++)
    {
        sum += xbee->data[i];
    }
    return (sum == xbee->checksum);
}


void write_to_file(FILE *file_output, uint8_t ok, XBEE *el)
{
    // fwrite(&xbee->len, sizeof(uint8_t), 1, file_output);
    // fwrite(xbee->data, sizeof(uint8_t), xbee->len, file_output);
    // fwrite(&xbee->checksum, sizeof(uint16_t), 1, file_output);
    fprintf(file_output, "%u\n", el->len);
    for (int i = 0; i < el->len; i++)
    {
        fprintf(file_output, "%02X ", el->data[i]);
    }
    fprintf(file_output, "\n");
    if (ok)
    {
        fprintf(file_output, "Checksum OK.\n");
    }
    else
    {
        fprintf(file_output, "Checksum NOT OK.\n");
    }
}


int main(int argc, char **argv)
{
    // mcview
    /*
    https://staff.cs.upt.ro/~valy/pt/
    xbee
    */


    /*
    gcc -Wall -o p .\main1.c
    ./p .\xbee.bin ok.txt nok.txt
    */

    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <key>\n", argv[0]);
        exit(1);
    }

    FILE *input;
    XBEE el;
    uint8_t temp;
    if ((input = fopen(argv[1], "rb")) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    FILE *fok;
    FILE *fnok;
    if ((fok = fopen(argv[2], "w")) == NULL)
    {
        perror(argv[2]);
        exit(1);
    }
    if ((fnok = fopen(argv[3], "w")) == NULL)
    {
        perror(argv[3]);
        exit(1);
    }

    while (1)
    {
        if (fread(&temp, sizeof(uint8_t), 1, input) != 1)
        {
            printf("No more data to read.\n");
            break;
        }
        if (temp != 0x7E)
        {
            printf("Invalid start byte: %02X\n", temp);
            break;
        }
        if (fread(&el.len, sizeof(uint8_t), 1, input) != 1)
        {
            printf("Failed to read length byte.\n");
            break;
        }
        if (el.len == 0)
        {
            printf("Zero length encountered.\n");
            
        }

        if (fread(el.data, sizeof(uint8_t), el.len, input) != el.len)
        {
            printf("Failed to read data bytes.\n");
            break;
        }

        if (fread(&el.checksum, sizeof(uint16_t), 1, input) != 1)
        {
            printf("Failed to read checksum bytes.\n");
            break;
        };

        printf("Length: %u\n", el.len);
        for (int i = 0; i < el.len; i++)
        {
            printf("%02X ", el.data[i]);
        }

        if (check(&el))
        {
            printf("\nChecksum OK.\n");
            write_to_file(fok, 1, &el);
        }
        else
        {
            printf("\nChecksum NOT OK.\n");
            write_to_file(fnok, 0, &el);
        }

        
        printf("\nChecksum: %04X\n", el.checksum);
    }
    printf("End of processing.\n");

    if (fclose(input) < 0)
    {
        perror("fclose input");
        exit(1);
    }
    if (fclose(fok) < 0)
    {
        perror("fclose fok");
        exit(1);
    }
    if (fclose(fnok) < 0)
    {
        perror("fclose fnok");
        exit(1);
    }
    return 0;
}