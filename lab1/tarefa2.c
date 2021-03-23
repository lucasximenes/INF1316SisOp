#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 

int main(void){
    int i, sum, status, j;
    for (j = 0; j < 3; j++){
        if (fork() == 0)
        {
            printf("Começa processo novo\n");
            for (i = 1000*(j), sum = 0; i < 1000*(j+1); i++)
            {
                sum += i;
                printf("valor de i = %d, soma parcial = %d e PID = %d\n", i, sum, getpid());
            }
            printf("Resultado da soma = %d\n", sum);
            printf("Terminando processo\n");
            exit(0);
        }
    }
    for (i = 0; i < 3; i++)
    {
        waitpid(-1, &status, 0);
    }
    
    return 0;
}