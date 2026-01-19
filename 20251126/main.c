#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *intersection_of_2_strings(char *s1, char *s2)
{
    char *s3 = malloc( (strlen(s1) + 1) * sizeof(char) );
    s3[0] = '\0'; 
    for (int i = 0; s1[i] != '\0'; i++)
    {
        if (s1[i] == s2[i])
        {
           s3[i] = s1[i];
        }
        else
        {
            s3[i] = '\0';
            break;
        }
    }
    return s3;
}

int main(void)
{
    char str1[100], str2[100];
    scanf("%100s", str1);
    scanf("%100s", str2);

    char *str3 = intersection_of_2_strings(str1, str2);
    printf("%s", str3);
    return 0;
}
