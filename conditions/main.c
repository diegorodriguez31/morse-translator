#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int age;
    printf("Quel est votre age ?\n");
    scanf("%d",&age);
    if (age >= 18){
        printf("Vous etes majeur (%d ans) ",age);
    } else {
        printf("Vous n etes pas majeur (%d ans) ",age);
    }
    return 0;
}
