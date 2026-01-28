#include <stdio.h>

int main()
{
    int total_apaitii=0;
    int v[26] = {0};
    int ch;
    while((ch = getchar()) != EOF)
    {
        total_apaitii++;
        if(ch >64 && ch<91)
        {
            v[ch-65]++;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (v[i] > 0)
        { 
            printf("%c Are frecventa %.2f%%\n", i + 'A', (v[i] * 100.0 / total_apaitii));
        }
    }
    return 0;
}