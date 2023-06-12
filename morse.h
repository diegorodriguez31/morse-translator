#define LONG_DELAI 400
#define NONPRESS_DELAI 1000
#define MORSETAILLE 7
#define BOUTON_GAUCHE 21
#define BOUTON_DROIT 29
#define LED_ROUGE 22
#define LED_VERTE 26
#define BARGRAPHE1 7
#define BARGRAPHE2 0
#define BARGRAPHE3 1
#define BARGRAPHE4 2
#define BARGRAPHE5 3
#define BARGRAPHE6 4
#define BARGRAPHE7 5
#define BARGRAPHE8 6


typedef enum{
	NONE,
	SHORT,
	LONG
}Bouton;

typedef struct{
	char lettre;
	Bouton signals[MORSETAILLE];
}morseAlphabet;


int tailleCouranteTableau(Bouton t[], int tailleMax);
char tradMorseChar(Bouton mot[],int taille);
int cmp_tab(Bouton t1[], Bouton t2[],int taille);
void tradCharMorseAffichage(char c);
int numeroChar(char c);
void afficherSignal(Bouton *t, int taille);
//void myInterrupt(void);
