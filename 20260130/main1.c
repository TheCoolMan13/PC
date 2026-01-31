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
        *budget_end = '\0';
    }

    return atol(budget);
}

int compare1(const void *a, const void *b)
{
    Movie *m1 = (Movie *)a;
    Movie *m2 = (Movie *)b;
    return m1->year - m2->year;
}

int compare2(const void *a, const void *b)
{
    Movie *m1 = (Movie *)a;
    Movie *m2 = (Movie *)b;
    return strcmp(m1->title, m2->title);
}

int compare3(const void *a, const void *b)
{
    Movie *m1 = (Movie *)a;
    Movie *m2 = (Movie *)b;
    return m1->budget - m2->budget;
}

int main()
{
    FILE *input;
    FILE *output1;
    FILE *output2;
    FILE *output3;

    const char *inputfilename = "movies.csv";
    const char *outputfilename1 = "moviesOUT1.txt";
    const char *outputfilename2 = "moviesOUT2.txt";
    const char *outputfilename3 = "moviesOUT3.txt";

    if ((input = fopen(inputfilename, "r")) == NULL)
    {
        fprintf(stderr, "Eroare deschidere input");
        exit(1);
    }
    if ((output1 = fopen(outputfilename1, "w")) == NULL)
    {
        fprintf(stderr, "Eroare descidere output");
        exit(1);
    }
    if ((output2 = fopen(outputfilename2, "w")) == NULL)
    {
        fprintf(stderr, "Eroare descidere output");
        exit(1);
    }
    if ((output3 = fopen(outputfilename3, "w")) == NULL)
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

    Movie *ListaFilme = malloc(MOVIE_CHUNK * sizeof(Movie));
    uint32_t MovieINDEX = 0;
    uint32_t MovieINDEX_LIMIT = MOVIE_CHUNK;
    while ((fgets(FILM, 1024, input)) != NULL)
    {
        if (MovieINDEX + 13 > MovieINDEX_LIMIT)
        {
            ListaFilme = realloc(ListaFilme, (MovieINDEX + MOVIE_CHUNK) * sizeof(Movie));
            MovieINDEX_LIMIT = MovieINDEX + MOVIE_CHUNK;
        }
        uint16_t YEAR = atoi(FILM);
        uint32_t BUDGET = ExtractBudget(FILM);
        char *TITLE = ExtractTitle(FILM);

        // NU LUAM IN CONSIDERARE FILMELE CARE AU O ',' IN TILTUL LOR
        if (BUDGET != 0)
        {
            ListaFilme[MovieINDEX].year = YEAR;
            ListaFilme[MovieINDEX].title = strdup(TITLE);
            ListaFilme[MovieINDEX].budget = BUDGET;

            printf("%hu %s %u\n", ListaFilme[MovieINDEX].year, ListaFilme[MovieINDEX].title, ListaFilme[MovieINDEX].budget);
            MovieINDEX++;
        }
    }
    MovieINDEX--;

    if (fclose(input) != 0)
    {
        perror(NULL);
        exit(-1);
    }

    // TASK PT OUT1  toate filmele sortate după anul apariției,
    qsort(ListaFilme, MovieINDEX, sizeof(Movie), compare1);
    for (int i = 0; i < MovieINDEX; i++)
    {
        fprintf(output1, "%hu, %u , %s \n", ListaFilme[i].year, ListaFilme[i].budget, ListaFilme[i].title);
    }
    if (fclose(output1) != 0)
    {
        perror(NULL);
        exit(-1);
    }

    // TASK PT OUT2  toate filmele sortate după anul apariției,
    qsort(ListaFilme, MovieINDEX, sizeof(Movie), compare2);
    for (int i = 0; i < MovieINDEX; i++)
    {
        fprintf(output2, "%hu, %u , %s \n", ListaFilme[i].year, ListaFilme[i].budget, ListaFilme[i].title);
    }
    if (fclose(output2) != 0)
    {
        perror(NULL);
        exit(-1);
    }

    // TASK PT OUT3  toate filmele sortate buget
    qsort(ListaFilme, MovieINDEX, sizeof(Movie), compare3);
    for (int i = 0; i < MovieINDEX; i++)
    {
        fprintf(output3, "%hu, %u , %s \n", ListaFilme[i].year, ListaFilme[i].budget, ListaFilme[i].title);
    }
    if (fclose(output3) != 0)
    {
        perror(NULL);
        exit(-1);
    }

    return 0;
}