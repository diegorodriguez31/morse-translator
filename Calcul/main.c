int main(int argc, char *argv[])
{
  int resultat = 0, nombre1 = 0, nombre2 = 0;

  // On demande les nombres 1 et 2 à l'utilisateur :

  printf("Entrez le nombre 1 : ");
  scanf("%d", &nombre1);
  printf("Entrez le nombre 2 : ");
  scanf("%d", &nombre2);

  // On fait le calcul :

  resultat = nombre1 + nombre2;

  // Et on affiche l'addition à l'écran :

  printf ("%d + %d = %d\n", nombre1, nombre2, resultat);

  int nombre = 2;

  nombre += 4; // nombre vaut 6...
  nombre -= 3; // ... nombre vaut maintenant 3
  nombre *= 5; // ... nombre vaut 15
  nombre /= 3; // ... nombre vaut 5
  nombre %= 3; // ... nombre vaut 2 (car 5 = 1 * 3 + 2)

  return 0;
}
