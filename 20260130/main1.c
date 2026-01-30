#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*

Se consideră un fișier csv (comma separated values) în care pe fiecare linie se află mai multe câmpuri separate prin virgulă. Fișierul conține informații despre filme. Pe fiecare linie se află câte o inregistrare ce reprezintă un film cu date despre acesta, date ce sunt separate prin virgulă. O linie are următoarea configurație (cap de tabel)
year,imdb,title,test,clean_test,binary,budget,domgross,intgross,code,budget_2013$,domgross_2013$,intgross_2013$,period code,decade code
Se va citi acest fișier în mod optim. Pentru fiecare înregistrare se vor extrage următoarele date: titlu, an, buget (title, year, budget). Se va proiecte și implementa o structură de date corespunzătoare. Se vor stoca aceste date intr-un tablou alocat dinamic. Se precizează că se consideră necunoscută dimensiunea fișierului ( a numărului de linii) - se va aloca minimul de memorie necesar pentru a stoca toate informațiile. Programul va scrie în fișierul out1.txt toate filmele sortate după anul apariției, în fișierul out2.txt toate filmele sortate după titlu iar în fișierul out3.txt toate filmele sortate după buget.

Fișierul de test poate fi descărcat folosind urmatoarea comandă:

wget http://staff.cs.upt.ro/~valy/pt/movies.csv
Se vor realiza mai multe variante de procesare si extragere de informații dintr-o linie de date: folosind strtok, folosind strchr, agloritm propriu prin parcurgere caracter cu caracter a unei linii deja citite din fișier.
*/

typedef struct
{
    uint16_t year;
    char *title;
    uint32_t budget;
} Movie;

#define MOVIE_CHUNK 1024

char *ExtractTitle(const char *input)
{
    char *year = strchr(input, ',');
    if (!year)
        return NULL;

    char *id = strchr(year + 1, ',');
    if (!id)
        return NULL;

    char *title = id + 1;
    if (!title)
        return NULL;

    char *finaltitlu = strchr(id + 1, ',');
    if (!finaltitlu)
        return NULL;
    else
    {
        *finaltitlu = '\0';
    }
    return title;
}

uint32_t ExtractBudget(const char *input)
{
    char *year = strchr(input, ',');
    if (!year)
    {
        perror(NULL);
        return 0;
    }
    char *id = strchr(year + 1, ',');
    if (!id)
    {
        perror(NULL);
        return 0;
    }
    char *title = strchr(id + 1, ',');
    if (!title)
    {
        perror(NULL);
        return 0;
    }
    char *test = strchr(title + 1, ',');
    if (!test)
    {
        perror(NULL);
        return 0;
    }
    char *clean_test = strchr(test + 1, ',');
    if (!clean_test)
    {
        perror(NULL);
        return 0;
    }
    char *binary = strchr(clean_test + 1, ',');
    if (!binary)
    {
        perror(NULL);
        return 0;
    }
    char *budget = binary + 1;

    char *budget_end = strchr(binary + 1, ',');
    if (!budget_end)
    {
        perror(NULL);
        return 0;
    }
    else
    {
        budget_end = '\0';
    }
    return atol(budget);
}

int main()
{
    FILE *input;
    FILE *output;

    const char *inputfilename = "movies.csv";
    const char *outputfilename = "moviesOUT1.txt";
    if ((input = fopen(inputfilename, "r")) == NULL)
    {
        fprintf(stderr, "Eroare deschidere input");
        exit(1);
    }
    if ((output = fopen(outputfilename, "w")) == NULL)
    {
        fprintf(stderr, "Eroare descidere output");
        exit(1);
    }

    char FILM[1024];
    // Extract header
    if ((fgets(FILM, 1024, input)) == NULL)
    {
        perror(NULL);
        exit(1);
    }

    Movie *ListaFilme = malloc(MOVIE_CHUNK);
    uint32_t MovieINDEX = 0;
    uint32_t MovieINDEX_LIMIT = MOVIE_CHUNK while ((fgets(FILM, 1024, input)) != NULL)
    {
        if (MovieINDEX + 1 > MovieINDEX_LIMIT)
        {
            /*

                AICI TREBE SA REALOCI SI DUPA SA VEZI CUM
                FACI RESTU TAK URILOR

            */
        }
        uint16_t YEAR = atoi(FILM);
        uint32_t BUDGET = ExtractBudget(FILM);
        char *TITLE = ExtractTitle(FILM);

        ListaFilme[MovieINDEX]->year = YEAR;
        ListaFilme[MovieINDEX]->title = TITLE;
        ListaFilme[MovieINDEX]->budget = BUDGET;
        MovieINDEX++;

        printf("%hu %s %u\n", YEAR, TITLE, BUDGET);
    }

    if (fclose(input) != 0)
    {
        perror(NULL);
        exit(-1);
    }
    if (fclose(output) != 0)
    {
        perror(NULL);
        exit(-1);
    }
    return 0;
}