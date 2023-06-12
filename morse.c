#include <stdlib.h>
#include <stdio.h>
#include "morse.h"
#include <wiringPi.h>
#include <malloc.h>
#include <time.h>
#include <string.h>


//scrutation régulière d'un état d'une entrée. On appelle ca du polling


static morseAlphabet morses[] =
{
  { 'a', { SHORT, LONG } },
  { 'b', { LONG, SHORT, SHORT, SHORT } },
  { 'c', { LONG, SHORT, LONG, SHORT } },
  { 'd', { LONG, SHORT, SHORT } },
  { 'e', { SHORT } },
  { 'f', { SHORT, SHORT, LONG, SHORT } },
  { 'g', { LONG, LONG, SHORT } },
  { 'h', { SHORT, SHORT, SHORT, SHORT } },
  { 'i', { SHORT, SHORT } },
  { 'j', { SHORT, LONG, LONG, LONG } },
  { 'k', { LONG, SHORT, LONG } },
  { 'l', { SHORT, LONG, SHORT, SHORT} },
  { 'm', { LONG, LONG } },
  { 'n', { LONG, SHORT } },
  { 'o', { LONG, LONG, LONG } },
  { 'p', { SHORT, LONG, LONG, SHORT } },
  { 'q', { LONG, LONG, SHORT, LONG } },
  { 'r', { SHORT, LONG, SHORT } },
  { 's', { SHORT, SHORT, SHORT } },
  { 't', { LONG } },
  { 'u', { SHORT, SHORT, LONG } },
  { 'v', { SHORT, SHORT, SHORT, LONG } },
  { 'w', { SHORT, LONG, LONG } },
  { 'x', { LONG, SHORT, SHORT, LONG } },
  { 'y', { LONG, SHORT, LONG, LONG } },
  { 'z', { LONG, LONG, SHORT, SHORT } },
  { '0', { LONG, LONG, LONG, LONG, LONG } },
  { '1', { SHORT, LONG, LONG, LONG, LONG } },
  { '2', { SHORT, SHORT, LONG, LONG, LONG } },
  { '3', { SHORT, SHORT, SHORT, LONG, LONG } },
  { '4', { SHORT, SHORT, SHORT, SHORT, LONG } },
  { '5', { SHORT, SHORT, SHORT, SHORT, SHORT } },
  { '6', { LONG, SHORT, SHORT, SHORT, SHORT } },
  { '7', { LONG, LONG, SHORT, SHORT, SHORT } },
  { '8', { LONG, LONG, LONG, SHORT, SHORT } },
  { '9', { LONG, LONG, LONG, LONG, SHORT } },
  { '.', { SHORT, LONG, SHORT, LONG, SHORT, LONG } },
  { ' ', { SHORT, SHORT, SHORT, SHORT, SHORT, SHORT} }
};

static int bargraphe[8] = 
{
 BARGRAPHE1,
 BARGRAPHE2,
 BARGRAPHE3,
 BARGRAPHE4,
 BARGRAPHE5,
 BARGRAPHE6,
 BARGRAPHE7,
 BARGRAPHE8
};


void main(){
	wiringPiSetup();
	pinMode(LED_ROUGE,OUTPUT);
	pinMode(LED_VERTE,OUTPUT);
	pinMode(BOUTON_GAUCHE,INPUT);
	pinMode(BARGRAPHE1, OUTPUT);
	pinMode(BARGRAPHE2, OUTPUT);
	pinMode(BARGRAPHE3, OUTPUT);
	pinMode(BARGRAPHE4, OUTPUT);
	pinMode(BARGRAPHE5, OUTPUT);
	pinMode(BARGRAPHE6, OUTPUT);
	pinMode(BARGRAPHE7, OUTPUT);
	pinMode(BARGRAPHE8, OUTPUT);
/*	
	if (wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &myInterrupt) < 0)

 {
   fprintf (stderr, "ISR ne se déclenche pas: %s\n", strerror (errno)) ;
 }*/
	
	int num = 0;
	char c;
	int choix;
	int aleatoire;
	int nbMot = 0;
	printf("1- Traduction Morse -> Francais\n");
	printf("2- Traduction Francais -> Morse\n");
	printf("3- Trouver le caractere\n");
	scanf("%d",&choix);
	switch(choix){
		case 1:
			printf("Tapez du morse sur le raspberry, la traduction va s'afficher ensuite\n");
			//définition du tableau qui recoit la traduction
		   	int taille = 20;
			char * traduction;
			traduction = (char *) malloc (taille * sizeof(char));

			int numTrad = 0;
			int temps = 0;
			//variable qui permet la condition d'arret
			int arret = 0;
			//définition du tableau qui recoit une lettre
			Bouton lettre[MORSETAILLE];

			//boucle pour l'arret de la phrase
		  	while(arret != 1){
		  		//boucle pour l'arret d'un caractere
				while(digitalRead(BOUTON_DROIT)==HIGH) {
					//boucle pour un signal
                    			while(digitalRead(BOUTON_GAUCHE)==LOW){
				      		delay(200);
				       		temps += 200;
                   			}

                   			if(temps >= 2000) {
                   				arret = 1;
                   			} else if (temps >= 400) {
                   				lettre[num] = LONG;
                   				num +=1;
                   			} else if (temps >= 200) {
                   				lettre[num] = SHORT;
                   				num +=1;
                   			}

			    		temps = 0;
				}

				digitalWrite(LED_VERTE,HIGH);
				delay(200);
				digitalWrite(LED_VERTE,LOW);
				delay(200);

				if(arret == 1) {
					break;
				}

				if(cmp_tab(lettre, morses[37].signals,6) && tailleCouranteTableau(lettre,MORSETAILLE) == 6){
					digitalWrite(bargraphe[nbMot],HIGH);
					nbMot ++;	
				}	

		        	c = tradMorseChar(lettre,tailleCouranteTableau(lettre,sizeof(lettre)/sizeof(Bouton)));

		    		tradCharMorseAffichage(c);
		    		num = 0;
		    		traduction[numTrad] = c;
		    		numTrad++;
		        	for(int i = 0; i < MORSETAILLE; i++) {
			    		lettre[i] = NONE;
			    	}
			  	if(numTrad == taille) {
		            		taille += 20;
		            		traduction = realloc(traduction,taille);
		    		}
			}
			for (int i = 0; i < 8; i++) {
				digitalWrite(bargraphe[i],LOW);
			}
			traduction[numTrad] = '\0';
			printf("%s\n",traduction);

			//gestion du fichier
			FILE* fichier1;
			fichier1 = fopen("AfficherFrancais","w");
			if(fichier1 == NULL){
				printf("Erreur d'ouverture du fichier\n");
			} else {
				printf("L'ouverture du fichier a fonctionné, passez le voir\n");
			}
			fprintf(fichier1, "%s", traduction);
			fclose(fichier1);
			free(traduction);
	 		break;

		case 2:
			printf("Saisissez une phrase et le raspberry va le convertir en morse\n");
			char phrase[1000];
			scanf("%s",&phrase);
			int taillePhrase = strlen(phrase);
            		int numeroCharPhrase;
			for(int i = 0;i < taillePhrase; i++){
                		numeroCharPhrase = numeroChar(phrase[i]);
				afficherSignal(morses[numeroCharPhrase].signals,tailleCouranteTableau(morses[numeroCharPhrase].signals,MORSETAILLE));
			}

			FILE* fichier2;
			fichier2 = fopen("AfficherMorse","w");
			if(fichier2 == NULL){
				printf("Erreur d'ouverture du fichier\n");
			} else {
				printf("L'ouverture du fichier a fonctionné, passez le voir\n");
			}
			fprintf(fichier2, "%s", phrase);
			fclose(fichier2);
			break;
		case 3:
			printf("Le raspberry va afficher un caractère en morse, devinez lequel\n");
			srand(time(NULL));
			aleatoire = rand()%37;
			c = morses[aleatoire].lettre;
			delay(1500);
			afficherSignal(morses[aleatoire].signals,tailleCouranteTableau(morses[aleatoire].signals,MORSETAILLE));
			char cEntree;
			scanf("\n%c",&cEntree);
			if(c == cEntree) {
				printf("Bien joué\n");
			} else {
				printf("Dommage\n");
			}

			FILE* fichier3;
			fichier3 = fopen("GagnéOuPerdu","w");
			if(fichier3 == NULL){
				printf("Erreur d'ouverture du fichier\n");
			}
			else{
				printf("L'ouverture du fichier a fonctionné, passez le voir\n");
			}
			fprintf(fichier3, "%c", traduction);
			fclose(fichier3);
			break;
		default: printf("Erreur, veuillez rentrer un choix valide : 1, 2 ou 3\n");
	}

}

int tailleCouranteTableau(Bouton t[], int tailleMax){
    int taille = 0;
    for(int i = 0; i < tailleMax; i++){
        if(t[i] == SHORT || t[i] == LONG) {
            taille++;
        }
    }
    return taille;
}

char tradMorseChar(Bouton mot[],int taille){
	for(int i = 0; i < 38; i++) {

		if(taille == tailleCouranteTableau(morses[i].signals,MORSETAILLE) && cmp_tab(mot,morses[i].signals,taille)) {
			return morses[i].lettre;
		}
	}
	return '!';
}

int cmp_tab(Bouton t1[], Bouton t2[],int taille) {
    for(int i = 0; i < taille; i++) {
        if(t1[i] != t2[i]) {
            return 0;
        }
    }
    return 1;
}

void tradCharMorseAffichage(char c) {
    for(int i = 0; i < 38; i++) {
        if(c == morses[i].lettre) {
            afficherSignal(morses[i].signals,tailleCouranteTableau(morses[i].signals,MORSETAILLE));
            break;
        }
    }
}

int numeroChar(char c) {
    for(int i = 0; i < 38; i++){
        if(c == morses[i].lettre) {
            return i;
        }
    }
}


void afficherSignal(Bouton *t, int taille) {
    for(int i = 0; i < taille; i++) {

        if(t[i] == SHORT) {
			digitalWrite(LED_ROUGE,HIGH);
			delay(200);
			digitalWrite(LED_ROUGE,LOW);
		} else if (t[i] == LONG) {
			digitalWrite(LED_ROUGE,HIGH);
			delay(600);
			digitalWrite(LED_ROUGE,LOW);

		}
		delay(300);
    }
/*    
void myInterrupt (void)
{
 ++Compteur ;
}*/
}
