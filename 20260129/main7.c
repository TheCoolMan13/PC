#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*


Să se scrie o funcție care primește ca argument un string ce conține în format text valori în hexazecimal pe două cifre hexazecimale fără prefixul
0x. Aceste valori reprezintă caractere conform tabelei ASCII. Funcția va decodifica textul și il va returna într-un string alocat dinamic.
Antetul funcției poate fi următorul:

char *hex2text(const char *hexstring);
Exemplu: hexstring = "616263" -> funcția va returna string-ul "abc"

Această problemă reprezintă inversa funcției dezvoltate la problema anterioară.

Pentru testare se pot folosi datele din fisierul ce se poate descarca prin comanda urmatoare



wget http://staff.cs.upt.ro/~valy/pt/hexlines.txt
Se recomanda ca citirea datelor sa se faca prin redirectarea intrarii standard.
*/

// char *hex2text(const char *hexstring);

#define CHUNK 100

int HexValue(const char charater)
{
    if (charater >= '0' && charater <= '9')
        return charater - '0';
    if (charater >= 'a' && charater <= 'f')
        return charater - 'a' + 10;
    if (charater >= 'A' && charater <= 'F')
        return charater - 'A' + 10;

    return 0;
}

char *hex2text(const char *hexString)
{
    char *result = (char *)malloc(CHUNK * sizeof(char));
    uint16_t len = strlen(hexString);
    char *CURR_INDEX = result;
    char *LIMIT_INDEX = result + CHUNK;
    for (int i = 0; i < len; i = i + 2)
    {
        CURR_INDEX = result + i / 2;
        if (CURR_INDEX + 1 >= LIMIT_INDEX)
        {
            result = (char *)realloc(result, (LIMIT_INDEX - result + CHUNK) * sizeof(char));
            if (result == NULL)
            {
                perror(NULL);
                exit(1);
            }
            CURR_INDEX = result + i / 2 + 1;
            LIMIT_INDEX = result + (i / 2) + CHUNK + 1;
        }

        // 61 = 6 * 16 + 1 = 97 -- -ASCII pt A
        uint16_t ASCII_value = (HexValue(hexString[i]) << 4) | HexValue(hexString[i + 1]);
        *(result + i / 2) = (char)ASCII_value;
    }
    result[len / 2] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Eroare argumente");
        exit(-1);
    }

    FILE *input;
    if ((input = fopen(argv[1], "r")) == NULL)
    {
        perror(NULL);
        exit(1);
    }

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), input))
    {
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (strlen(buffer) > 0)
        {
            char *decoded = hex2text(buffer);
            if (decoded)
            {
                printf("%s \n", decoded);
                free(decoded);
            }
            else
            {
                perror(NULL);
                exit(-1);
            }
        }
    }
    fclose(input);
    return 0;
}