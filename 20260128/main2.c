/*
Scrieți un program, folosind getchar() și putchar(), care, primind la stdin redirectat un
 fișier ce conține un cod C, va printa la stdout același fișier dar fără comentarii.
 Practic, programul va elimina comentariile din fișierul C primit prin redirectare de stdin
 și va printa rezultatul la stdout
*/
#include <stdio.h>
#include <stdlib.h>
//   ana " are "" mere/ si are "" bere """ adhawda /* dawdwda
int main()
{
    int flag1 = 0, flag2 = 0;
    int ch;
    while ((ch = getchar()) != EOF)
    {
        flag1 = 0, flag2 = 0;
        if (ch == '/')
        {
            flag1 = 1;
            if ((ch = getchar()) != EOF)
            {
                if (ch != '/')
                {
                    putchar('/'), putchar(ch);
                }
                else
                {
                    while ((ch = getchar()) != '\t')
                    {
                    }
                }
            }
            else
            {
                return 0;
            }
        }
        if (ch == '"')
        {
            flag2 = 1;
            if ((ch = getchar()) != EOF)
            {
                if (ch != '"')
                {
                    putchar('"'), putchar(ch);
                }
            }
            if (ch == '"')
            {
                if ((ch = getchar()) != EOF)
                {
                    if (ch != '"')
                    {
                        putchar('""'), putchar(ch);
                    }
                    else
                    {
                        int out = 0;
                        while ((out != 1))
                        {
                            if ((ch = getchar()) == '"')
                            {
                                if ((ch = getchar()) == '"')
                                {
                                    if ((ch = getchar()) == '"')
                                        out = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (!flag1 && !flag2)
        {
            putchar(ch);
        }
    }
    return 0;
}