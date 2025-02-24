#include <stdio.h>
#include <unistd.h>

#define LECTURE 0
#define ECRITURE 1

int main()
{
    int tube[2];
    pipe(tube);

    //Parent
    if(fork())
    {
        char msg[] = "Hello depuis le parent";
        write(tube[ECRITURE], msg, sizeof(msg));
    }
    //Enfant
    else{
        char buf[100];
        read(tube[LECTURE], buf, sizeof(buf));
        printf("Enfant a reçu : %s\n", buf);
    }
}