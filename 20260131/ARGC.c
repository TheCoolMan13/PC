#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Pentru tolower si toupper

#define LINE_LIMIT 1024

// Functie care returneaza tipul de optiune sau 0 daca e nume de fisier
int GetOption(char *arg) {
    if (arg[0] == '-') {
        if (arg[1] == 'o') return 1;
        if (arg[1] == 'l') return 2;
        if (arg[1] == 'u') return 3;
    }
    return 0;
}

// Functiile modifica sirul "in-place" (direct in memorie)
void apply_mode(char *line, int mode) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (mode == 2) line[i] = tolower(line[i]);
        else if (mode == 3) line[i] = toupper(line[i]);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Utilizare: %s [-o|-l|-u] fisier1 ...\n", argv[0]);
        return 1;
    }

    int current_mode = 1; // Implicit '-o' (original)
    FILE *input = NULL;
    char line[LINE_LIMIT];

    for (int i = 1; i < argc; i++) {
        int opt = GetOption(argv[i]);

        if (opt != 0) {
            // Daca argumentul e o optiune, doar actualizam starea curenta
            current_mode = opt;
        } else {
            // Daca argumentul e un fisier, il deschidem si il procesam cu starea curenta
            input = fopen(argv[i], "r");
            if (input == NULL) {
                perror(argv[i]); // Afiseaza numele fisierului care a esuat
                continue; // Trecem la urmatorul fisier, nu oprim tot programul
            }

            while (fgets(line, LINE_LIMIT, input) != NULL) {
                apply_mode(line, current_mode);
                printf("%s", line);
            }
            printf("\n");
            fclose(input);
        }
    }

    return 0;
}