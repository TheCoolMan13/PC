/*
Se consideră un fișier csv (comma separated values) în care pe
fiecare linie se află mai multe câmpuri separate prin virgulă.
Fișierul conține informații despre filme. Pe fiecare linie se
află câte o inregistrare ce reprezintă un film cu date despre acesta, date ce sunt separate prin virgulă. O linie are următoarea configurație (cap de tabel)
year,imdb,title,test,clean_test,binary,budget,domgross,intgross,
code,budget_2013$,domgross_2013$,intgross_2013$,period code,decade
code
Se va citi acest fișier în mod optim. Pentru fiecare înregistrare
se vor extrage următoarele date: titlu, an, buget
(title, year, budget).
Se va proiecte și implementa o structură de date corespunzătoare.
 Se vor stoca aceste date intr-un tablou alocat dinamic.
 Se precizează că se consideră necunoscută dimensiunea fișierului
 ( a numărului de linii) - se va aloca minimul de memorie necesar
   pentru a stoca toate informațiile. Programul va scrie în fișierul
   out1.txt toate filmele sortate după anul apariției, în fișierul
   out2.txt toate filmele sortate după titlu iar în fișierul
   out3.txt toate filmele sortate după buget.

Fișierul de test poate fi descărcat folosind urmatoarea comandă:

wget http://staff.cs.upt.ro/~valy/pt/movies.csv
*/
// Trebuie sa extrag anu titlu si bugetul
// Facem numa pt out1.txt

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MOVIE_CHUNK 1024
typedef struct
{
    char title[200];
    uint16_t year;
    uint64_t budget;
} MOVIE;

int compare1(const void *a, const void *b)
{
    MOVIE *mov1 = (MOVIE *)a;
    MOVIE *mov2 = (MOVIE *)b;
    return mov1->year - mov2->year;
}

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
    char *finaltitle = strchr(title, ',');
    if (!finaltitle)
        return NULL;
    else
    {
        *finaltitle = '\0';
    }
    return title;
}

uint64_t ExtractBudget(const char *input)
{
    char *year = strchr(input, ',');
    if (!year)
        return 0;
    char *id = strchr(year + 1, ',');
    if (!id)
        return 0;
    char *title = strchr(id + 1, ',');
    if (!title)
        return 0;
    char *test = strchr(title + 1, ',');
    if (!test)
        return 0;
    char *clean_test = strchr(test + 1, ',');
    if (!clean_test)
        return 0;
    char *binary = strchr(clean_test + 1, ',');
    if (!binary)
        return 0;
    char *budget = binary + 1;
    char *finalbudget = strchr(binary + 1, ',');
    if (!finalbudget)
        return 0;
    else
    {
        *finalbudget = '\0';
    }
    return atoll(budget);
}

int main(int argc, char **argv)
{
    // ./movies movies.csv out1.txt
    if (argc != 3)
    {
        fprintf(stderr, "EROARE ARGUMENTE");
        exit(1);
    }
    FILE *input = NULL;
    FILE *output = NULL;
    if ((input = fopen(argv[1], "r")) == NULL)
    {
        perror(NULL);
        exit(1);
    }
    if ((output = fopen(argv[2], "w")) == NULL)
    {
        perror(NULL);
        fclose(input);
        exit(1);
    }

    MOVIE *MOVIES = malloc(MOVIE_CHUNK * sizeof(MOVIE));
    uint32_t MovieIndex = 0;
    uint32_t MovieIndexMax = MOVIE_CHUNK;

    char line[1024];
    fgets(line, sizeof(line), input);

    while (fgets(line, sizeof(line), input) != NULL)
    {
        if (MovieIndex + 1 > MovieIndexMax)
        {
            MOVIES = realloc(MOVIES, (MovieIndex + MOVIE_CHUNK) * sizeof(MOVIE));
            MovieIndexMax = MovieIndex + MOVIE_CHUNK;
        }
        uint16_t an = atoi(line);
        uint64_t buget = ExtractBudget(line);
        char *titlu = ExtractTitle(line);

        if (buget != 0 && an != 0)
        {
            MOVIES[MovieIndex].year = an;
            MOVIES[MovieIndex].budget = buget;
            strcpy(MOVIES[MovieIndex].title, titlu);
            printf("%hu %s %lu \n", MOVIES[MovieIndex].year, MOVIES[MovieIndex].title, MOVIES[MovieIndex].budget);
            MovieIndex++;
        }
    }
    MovieIndex--;
    if (MOVIES == NULL)
    {
        perror(NULL);
        exit(1);
    }
    qsort(MOVIES, MovieIndex, sizeof(MOVIE), compare1);
    for (uint32_t i = 0; i < MovieIndex; i++)
    {
        fprintf(output, "%hu %s %lu \n", MOVIES[i].year, MOVIES[i].title, MOVIES[i].budget);
    }
    free(MOVIES);
    if (fclose(input) != 0)
    {
        perror(NULL);
        exit(1);
    }
    if (fclose(output) != 0)
    {
        perror(NULL);
        exit(1);
    }
    return 0;
}