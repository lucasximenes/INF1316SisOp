#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 

int main(void){
    int i, sum, status;
    if (fork() != 0)
    { // PAI
        printf("Processo pai foi criado\n");
        for (i = 0, sum = 0; i < 1000; i++)
        {
            sum += i;
            printf("valor de i = %d, soma parcial = %d e PID = %d\n", i, sum, getpid());    

        }
        printf("Resultado da soma = %d\n", sum);
        waitpid(-1, &status, 0);
        printf("Processo pai vai terminar\n");
        exit(0);
    }
    else
    {
        if (fork() != 0)
        { // FILHO
            printf("Filho criado\n");
            for (i = 1000, sum = 0; i < 2000; i++)
            {
                sum += i;
                printf("valor de i = %d, soma parcial = %d e PID = %d\n", i, sum, getpid());   

            }
            printf("Resultado da soma = %d\n", sum);
            waitpid(-1, &status, 0);
            printf("Processo filho vai terminar\n");
            exit(0);
        }
        else
        {
            printf("Neto criado\n");
            for (i = 2000, sum = 0; i < 3000; i++)
            {
                sum += i;
                printf("valor de i = %d, soma parcial = %d e PID = %d\n", i, sum, getpid());   
            }
            printf("Resultado da soma = %d\n", sum);
            printf("Processo neto vai terminar\n");
            exit(0);
        }
    }
    return 0;
}