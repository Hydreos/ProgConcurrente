#include <stdio.h>
#include <unistd.h>

int main() {
  int id = 0;
  for (int i = 1; i < 11; i++) {

    if (fork() == 0) {
      id = i;
      break;
    }
  }

  if (id) {
    for (int i = 0; i < 10; i++) {
      printf("Processus %d : %d\n", id, i);
    }
  }
}