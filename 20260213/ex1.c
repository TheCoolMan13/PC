#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define LETTER_CHUNK 99

char *oct2text(const char *src)
{
    // Calculate actual length: each character is 3 octal digits
    int src_len = strlen(src);
    // Strip newline if present
    if (src[src_len - 1] == '\n')
        src_len--;

    int num_chars = src_len / 3;
    char *Decoded = malloc(num_chars + 1);

    if (!Decoded)
        return NULL; // Always check your malloc!

    for (int i = 0; i < num_chars; i++)
    {
        int d1 = src[i * 3] - '0';
        int d2 = src[i * 3 + 1] - '0';
        int d3 = src[i * 3 + 2] - '0';

        Decoded[i] = (char)(d1 * 64 + d2 * 8 + d3);
    }
    Decoded[num_chars] = '\0';
    return Decoded;
}

int main(void)
{
    char litere[1024]; // Increased size as your input lines look long
    while (fgets(litere, sizeof(litere), stdin))
    {
        char *DecodedText = oct2text(litere);
        if (DecodedText)
        {
            printf("%s\n", DecodedText);
            free(DecodedText); // Don't forget to free what you malloc'd!
        }
    }
    return 0;
}
