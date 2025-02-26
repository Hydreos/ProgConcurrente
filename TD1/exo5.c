#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LECTURE 0
#define ECRITURE 1
#define FALSE 0
#define TRUE 1

int main() {
  int suivant[2];
  pipe(suivant);

  // Parent
  if (fork()) {
    close(suivant[LECTURE]); // Le parent n’a pas besoin de lire
    for (int i = 2; i < 20; i++) {
      write(suivant[ECRITURE], &i, sizeof(i));
    }
    close(suivant[ECRITURE]); // Ferme après écriture
    exit(0); // Termine le parent
  }

  // Enfant
  else {
    int prime = 0;
    int nombre;
    int enfant = FALSE;
    int precedent = suivant[LECTURE];
    close(suivant[ECRITURE]); // L’enfant n’écrit pas dans le premier pipe

    while (1) {
      int nbytes = read(precedent, &nombre, sizeof(int));
      if (nbytes <= 0) { // Fin des données ou erreur
        close(precedent);
        if (enfant == TRUE) {
          close(suivant[ECRITURE]); // Ferme le pipe vers l’enfant suivant
        }
        exit(0);
      }

      if (prime == 0) {
        printf("%d\n", nombre);
        prime = nombre;
      }
      else if (nombre % prime != 0) {
        if (enfant == FALSE) {
          pipe(suivant);
          if (fork()) { // Parent
            close(suivant[LECTURE]); // Le parent n’a pas besoin de lire
            enfant = TRUE;
          }
          else { // Nouvel enfant
            close(precedent); // Ferme l’ancien pipe
            precedent = suivant[LECTURE];
            close(suivant[ECRITURE]); // Le nouvel enfant n’écrit pas
            prime = 0; // Réinitialise pour recevoir un nouveau prime
            continue;
          }
        }
        if (enfant == TRUE) {
          write(suivant[ECRITURE], &nombre, sizeof(int));
        }
      }
    }
  }
}