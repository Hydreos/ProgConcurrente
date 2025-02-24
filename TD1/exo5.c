#include <unistd.h>

#define LECTURE 0
#define ECRITURE 1
#define FALSE 0
#define TRUE 1

int main() {

  int tube[2];

  // Parent
  if (fork()) {
    for (int i = 2; i < 20; i++) {
      write(tube[ECRITURE], &i, sizeof(i));
    }
  }

  // Enfant
  else {
    int prime = 0;
    int nombre;

    if (prime == 0) {
      read(tube[LECTURE], &prime, sizeof(int));
    }

    while(1) {
      if()
    }
  }
}