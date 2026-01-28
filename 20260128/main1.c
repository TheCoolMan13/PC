#include <stdio.h>
#include <stdlib.h>

/*

Scrieți un program, folosind getchar() și putchar() prin care se numără cuvintele de la stdint. 
Se consideră un cuvânt ca fiind o secvență de litere mici și/sau mari care despărțite prin unul 
sau mai multe spații, tab-uri, linii noi și EOF. Testarea se va face atât clasic prin scriere
 la stdin cât și prin redirectare cu un fișier text realizat inainte ca și caz de test catre 
 intrarea standard a programului
*/

int main()
{
    char ch;
    int contor = 1;
    while((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            contor++;
        }
    }

    printf("Numarul de cuvinte este: %d\n", contor);
    return 0;
}