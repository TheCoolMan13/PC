#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 256

char *read_line(void)
{

    char *line = NULL;
    int ch, index = 0, curent_size = 0;
    while ((ch = getchar()) != EOF)
    {
        if (index == curent_size)
        {
            curent_size += CHUNK;
            if ((line = realloc(line, curent_size * sizeof(char))) == NULL)
            {
                // free(line);
                return NULL;
            }
        }
        if (ch == '\n')
        {
            break;
        }
        line[index++] = (char)ch;
    }
    if (index == curent_size)
    {
        curent_size++;
        if (line == NULL)
        {
            return NULL;
        }
        if ((line = realloc(line, curent_size * sizeof(char))) == NULL)
        {

            return NULL;
        }
    }
    line[index] = '\0';
    return line;
}

char **read_lines(void)
{
    char **lines = NULL;
    int curent_size = 0;
    int index = 0;
    char *line;
    while ((line = read_line()) != NULL)
    {
        if (index == curent_size)
        {
            curent_size += CHUNK;
            if ((lines = realloc(lines, curent_size * sizeof(char *))) == NULL)
            {

                return NULL;
            }
        }
        lines[index++] = line;
    }
    if(lines == NULL)
    {
        return NULL;
    }
    if (index == curent_size)
    {
        curent_size++;
        if ((lines = realloc(lines, curent_size * sizeof(char *))) == NULL)
        {
            return NULL;
        }
    }
    lines[index] = NULL;
    return lines;
}


void print_lines(char **lines)
{
    char **p = lines;
    while (*p != NULL)
    {
        printf("%s\n", *p);
        p++;
    }
}

void free_lines(char **lines)
{
    char **p = lines;
    while (*p != NULL)
    {
        free(*p);
        p++;
    }
    free(lines);
}

int main(void)
{
    char **lines = NULL;
    if((lines = read_lines() ) != NULL)
    {
        print_lines(lines);
    }
    free_lines(lines);
    return 0;
}