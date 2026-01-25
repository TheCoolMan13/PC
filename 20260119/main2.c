#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
retrive resolution of bmp
look at wikipedia page for bmp file format header
https://en.wikipedia.org/wiki/BMP_file_format
*/

int main(void)
{
    FILE *f;
    if((f = fopen("images.bmp", "rb")) == NULL)
    {
        perror("image.bmp");
        exit(1);
    }

    char header_field[3];
    memset(header_field, 0, sizeof(header_field));
    fread(header_field, sizeof(char), 2, f);
    printf("Header field: %s\n", header_field);

    uint32_t bmp_size;
    fread(&bmp_size, sizeof(uint32_t), 1, f);
    printf("BMP size: %u bytes\n", bmp_size);
    fseek(f, 18, SEEK_SET); 

    uint16_t width;
    fread(&width, sizeof(uint16_t), 1, f);
    printf("Width: %u pixels\n", width);

    uint16_t height;
    fread(&height, sizeof(uint16_t), 1, f);
    printf("Height: %u pixels\n", height);

    // ASTA DE MAI SUS NU MERGE 100% , rezolva singur

    fclose(f);
    return 0;
}
