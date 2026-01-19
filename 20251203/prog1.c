#include <stdio.h>
#include <stdlib.h>

struct animals
{
    char name[50];
    int weight;
};


int main() {
    struct animals animal[2];
    for(int i = 0; i < 2; i++) {
        printf("Enter name of animal %d: ", i + 1);
        scanf("%49s", animal[i].name);
        printf("Enter weight of animal %d: ", i + 1);
        scanf("%d", &animal[i].weight);
    }
    printf("\nYou entered:\n");
    for(int i = 0; i < 2; i++) {
        printf("Animal %d: Name = %s, Weight = %d\n", i + 1, animal[i].name, animal[i].weight);
    }
    return 0;
}