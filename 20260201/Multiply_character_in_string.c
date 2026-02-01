#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define CHUNK 100

int is_in_list(const char *list, const char target)
{
    for (uint16_t i = 0; i < strlen(list); i++)
    {
        if (list[i] == target)
            return 1;
    }
    return 0;
}

char *multiply_character_in_string(uint16_t count, const char *char_list, const char *str)
{
    char *result = malloc(strlen(str) * sizeof(char));
    uint32_t INDEX_maxim = strlen(str);
    uint32_t INDEX_curent = 0;
    for (uint16_t i = 0; i < strlen(str); i++)
    {
        if (is_in_list(char_list, str[i]))
        {
            if (INDEX_curent + count + 1 > INDEX_maxim)
            {
                result = realloc(result, (INDEX_curent + CHUNK) * sizeof(char));
                INDEX_maxim += CHUNK;
            }
            for (uint16_t j = 0; j < count; j++)
            {
                result[INDEX_curent++] = str[i];
            }
        }
        else
        {
            if (INDEX_curent + 1 > INDEX_maxim)
            {
                result = realloc(result, (INDEX_curent + CHUNK) * sizeof(char));
                INDEX_maxim += CHUNK;
            }
            result[INDEX_curent++] = str[i];
        }
    }
    result[INDEX_curent] = '\0';
    return result;
}

int main()
{
    char list[CHUNK];
    uint16_t count;
    char str[CHUNK * 10];
    printf("Introdu lista de caractere (ex: rmn!): ");
    if (fgets(list, sizeof(list), stdin) == NULL)
    {
        perror(NULL);
        exit(1);
    }
    list[strcspn(list, "\n")] = 0;
    printf("Introdu de cate ori sa se multiplice: ");
    if (scanf("%hu", &count) != 1)
    {
        fprintf(stderr, "Eroare la citirea numarului.\n");
        exit(1);
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    printf("Introdu sirul de caractere (ex: ana are mere!): ");
    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        perror(NULL);
        exit(1);
    }
    str[strcspn(str, "\n")] = 0;
    char *Result = multiply_character_in_string(count, list, str);
    if (Result)
    {
        printf("\nOriginal: %s\n", str);
        printf("Resultat: %s\n", Result);
        free(Result);
    }
    else
    {
        perror(NULL);
        exit(-1);
    }

    return 0;
}