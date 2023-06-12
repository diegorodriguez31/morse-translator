#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int difficulte() {
    int max = 100;
    int dif;
    printf("Chosissez un niveau de diffculte :\n 1- Chiffre de 0 a 100\n 2- Chiffre de 0 a 1000\n 3- Chiffre de 0 a 10000\n");
    scanf("%d",&dif);
    if (dif == 1) {
        max = 100; printf("choix 1\n");
    } else if (dif == 2) {
        max = 1000; printf("choix 2\n");
    } else if (dif == 3) {
        max = 10000; printf("choix 3\n");
    } else {
        printf("Erreur : choix par defaut (100-0)\n");
    }
    return max;
}

int main(){
    srand(time(NULL));
    int reponse = 1;
    do {
    //menu nombre joeur
    printf("Nombre de joueur :\n -1 joueur -> 1\n -2 joueurs -> 2\n");
    int nbJoueur;
    printf("Combien de joueur ? ");
    scanf("%d",&nbJoueur);
    while (nbJoueur != 1 && nbJoueur != 2){
        printf("Nombre de joueur invalide (1 ou 2 joueurs) : ");
        scanf("%d",&nbJoueur);
    }

    //generation nombre
    int nombreMystere;
    if (nbJoueur == 1) {

            //menu difficulte
            const int MIN = 1;
            int nombreMax = difficulte();


        nombreMystere = (rand() % (nombreMax - MIN + 1)) + MIN;
    } else {
        printf("Choisissez le nombre : ");
        scanf("%d",&nombreMystere);
    }

    //boucle jeu
    int compteur = 0;
    int nbDonne;
    do {
        printf("Quel est le nombre ? ");
        scanf("%d",&nbDonne);
        if (nbDonne > nombreMystere) {
            printf("C est moins ! \n");
        } else if (nbDonne < nombreMystere) {
            printf("C est plus ! \n");
        }
        compteur++;
     } while (nbDonne != nombreMystere);

     printf("Bravo, tu as trouve le nombre mystere (%d) en %d coup(s)\n",nombreMystere,compteur);
     printf("Voulez vous rejouer ? (1/0) \n");
     int reponse;
     scanf("%d",&reponse);

    } while (reponse == 1);
}
