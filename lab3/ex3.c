#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int V[4000];

typedef struct pair
{
    int val;
    int index;
} pair;


int main()
{
    int cont, d, i, greatest = 0, greatest_index = 0, aux, status;
    for (cont = 0; cont < 4000; cont++)
    {
        aux = rand();
        if (aux > greatest){
            greatest_index = cont;
            greatest = aux;
        }
        V[cont] = aux;
    }
    printf("\nMaior valor do vetor é %d e foi colocado no índice %d\n", greatest, greatest_index);
    for (d = 0; d < 4; d++)
    {
        if (fork() == 0)
        {
            int greatest_son = 0;
            printf("\nComeca filho buscando o maior valor entre os indices %d e %d, PID = (%d)\n", d * 1000, (d + 1) * 1000 - 1, getpid());
            for (i = d * 1000; i < ((d + 1) * 1000); i++)
            {
                if (V[i] == greatest)
                {
                    printf("\nMaior valor == %d foi achado no indice %d, PID = (%d)\n", V[i], i, getpid());
                    greatest_son = V[i];
                }
            }
            
            exit(0);
        }
    }

    for (d = 0; d < 4; d++)
        waitpid(-1, &status, 0);

    
    return 0;
}