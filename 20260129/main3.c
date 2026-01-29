#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Jocul fazan: se citesc de la tastatură cuvinte separate prin spaţii albe (spaţiu, TAB sau ENTER), până la întâlnirea cuvântului vid. Pornind de la cuvintele citite, se construieşte un şir de caractere după următoarele reguli:
    - Primul cuvânt citit se adaugă la şirul de caractere
    - Fiecare din următoarele cuvinte citite se adaugă la şirul de caractere dacă ultimele două litere ale şirului coincid cu primele două litere ale cuvântului (nu se face distincţie între literele mici şi cele mari);
Cuvintele adăugate la şirul de caractere sunt despărţite de caracterul ’-’. Să se afişeze şirul astfel construit. Programul va folosi alocare dinamică astfel încât spaţiul de memorie utilizat să fie minim.
Spre exemplu, pentru intrarea:

Fazan Antic Noe icoana Egipt naftalina nimic Narcisa trei altceva santier iarba Caine Pisica erudit

se afişează:

Fazan-Antic-icoana-naftalina-Narcisa-santier-erudit

*/
#define LungimeMaximaCuvant 20
int main()
{
    char *cuvant_citit = NULL;
    cuvant_citit = (char *)malloc(LungimeMaximaCuvant * sizeof(char));

    char *Sir_rezultant = NULL;

    // Citim primul cuvant
    if (fgets(cuvant_citit, LungimeMaximaCuvant, stdin) != 0)
    {
        cuvant_citit[strcspn(cuvant_citit, "\n")] = 0;
        Sir_rezultant = (char *)realloc(Sir_rezultant, sizeof(cuvant_citit));
        strcpy(Sir_rezultant, cuvant_citit);
    }

    while (fgets(cuvant_citit, LungimeMaximaCuvant, stdin) != 0 && cuvant_citit[0] != '\n')
    {
        cuvant_citit[strcspn(cuvant_citit, "\n")] = 0;
        if (Sir_rezultant[strlen(Sir_rezultant) - 1] == cuvant_citit[1])
        {
            if (Sir_rezultant[strlen(Sir_rezultant) - 2] == cuvant_citit[0])
            {
                if ((Sir_rezultant = (char *)realloc(Sir_rezultant, strlen(Sir_rezultant) + strlen(cuvant_citit) + 1)) == NULL)
                {
                    perror(NULL);
                    exit(-1);
                }
                strcat(Sir_rezultant, "-");
                strcat(Sir_rezultant, cuvant_citit);
            }
        }
    }
    Sir_rezultant[strlen(Sir_rezultant)] = 0;
    printf("\n%s", Sir_rezultant);
    free(Sir_rezultant);
    return 0;
}