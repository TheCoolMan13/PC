#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 512
struct posix_header
{                       /* byte offset */
    char name[100];     /* 0 */
    char mode[8];       /* 100 */
    char uid[8];        /* 108 */
    char gid[8];        /* 116 */
    char size[12];      /* 124 */
    char mtime[12];     /* 136 */
    char chksum[8];     /* 148 */
    char typeflag;      /* 156 */
    char linkname[100]; /* 157 */
    char magic[6];      /* 257 */
    char version[2];    /* 263 */
    char uname[32];     /* 265 */
    char gname[32];     /* 297 */
    char devmajor[8];   /* 329 */
    char devminor[8];   /* 337 */
    char prefix[155];   /* 345 */
                        /* 500 */
};

void Init_tar_header(struct posix_header *h, const char *filename, long filesize)
{
    memset(h, 0, sizeof(struct posix_header));
    memcpy(h->mode, "0000777", 7);
    memcpy(h->uid, "0001750", 7);
    memcpy(h->gid, "0001750", 7);
    memcpy(h->mtime, "15137656773", 11);
    h->typeflag = '0';
    memcpy(h->magic, "ustar", 6);
    memcpy(h->version, "  ", 2);

    strncpy(h->uname, "ticusantitus", 31);
    strncpy(h->gname, "ticusantitus", 31);
    strncpy(h->name, filename, 99);

    sprintf(h->size, "%011lo", filesize);

    unsigned int sum = 0;
    memset(h->chksum, ' ', 8);

    unsigned char *ptr = (unsigned char *)h;
    for (int i = 0; i < 512; i++)
    {
        sum += ptr[i];
    }

    sprintf(h->chksum, "%06o", sum);
    h->chksum[6] = '\0';
    h->chksum[7] = ' ';
}

long get_file_size(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
        return -1;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

void EXTRAGERE_ARHIVA(char *input)
{
    FILE *tar_file = fopen(input, "rb");
    if (!tar_file)
    {
        perror(input);
        return;
    }

    struct posix_header HEADER;
    while (fread(&HEADER, BLOCK_SIZE, 1, tar_file) > 0)
    {
        if (HEADER.name[0] == '\0')
            break;

        long size = strtol(HEADER.size, NULL, 8);
        FILE *out = fopen(HEADER.name, "wb");
        if (!out)
        {
            perror(HEADER.name);
            fseek(tar_file, ((size + 511) / 512) * 512, SEEK_CUR);
            continue;
        }

        long remaining = size;
        char buffer[BLOCK_SIZE];
        while (remaining > 0)
        {
            if (fread(buffer, 1, BLOCK_SIZE, tar_file) == 0)
                break;
            size_t to_write = (remaining > BLOCK_SIZE) ? BLOCK_SIZE : remaining;
            fwrite(buffer, 1, to_write, out);
            remaining -= BLOCK_SIZE;
        }
        fclose(out);
        printf("Extras: %s (%ld bytes)\n", HEADER.name, size);
    }
    fclose(tar_file);
}

void CREARE_ARHIVA(char *input_filename, FILE *tar_file)
{
    long size = get_file_size(input_filename);
    if (size < 0)
        return;

    unsigned char header_block[BLOCK_SIZE];
    memset(header_block, 0, BLOCK_SIZE);

    struct posix_header *HEADER = (struct posix_header *)header_block;
    Init_tar_header(HEADER, input_filename, size);

    fwrite(header_block, BLOCK_SIZE, 1, tar_file);

    FILE *src = fopen(input_filename, "rb");
    if (!src)
        return;
    char buffer[BLOCK_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BLOCK_SIZE, src)) > 0)
    {
        if (bytes_read < BLOCK_SIZE)
            memset(buffer + bytes_read, 0, BLOCK_SIZE - bytes_read);
        fwrite(buffer, BLOCK_SIZE, 1, tar_file);
    }
    fclose(src);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "EROARE ARGUMENTE\n");
        exit(1);
    }
    else
    {
        if (strcmp(argv[1], "c") == 0 || strcmp(argv[1], "C") == 0)
        {
            if (argc < 3)
            {
                fprintf(stderr, "Lipsesc fisierele!\n");
                return 1;
            }
            printf("OPTION 2 : CREARE ARHIVA\n");
            FILE *output_archive = NULL;

            if ((output_archive = fopen("MY_TAR.tar", "wb")) == NULL)
            {
                fprintf(stderr, "EROARE DESCHIDERE FISIER\n");
                exit(1);
            }

            for (int i = 2; i < argc; i++)
            {
                if (argv[i])
                {
                    CREARE_ARHIVA(argv[i], output_archive);
                }
                else
                {
                    fprintf(stderr, "EROARE ARGUMENTE DE CREARE\n");
                    exit(1);
                }
            }

            char null_blocks[BLOCK_SIZE * 2];
            memset(null_blocks, 0, BLOCK_SIZE * 2);
            fwrite(null_blocks, BLOCK_SIZE * 2, 1, output_archive);

            fclose(output_archive);
        }
        else if (strcmp(argv[1], "x") == 0 || strcmp(argv[1], "X") == 0)
        {
            printf("OPTION 1 : EXTRAGERE ARHIVA\n");
            if (argc > 2)
                EXTRAGERE_ARHIVA(argv[2]);
            else
                fprintf(stderr, "Specifica arhiva pentru extragere!\n");
        }
        else
        {
            fprintf(stderr, "EROARE ARGUMENT EXTRACT/CREARE\n");
        }
    }
    return 0;
}