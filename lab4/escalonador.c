#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define EVER ;;
// Alunos: Lucas Ximenes Guilhon e Miguel Fagundes Vuori

int inRange(int pid_pai,int pid, int sons);
int inRange(int pid_pai,int pid, int sons)
{
    if(pid - pid_pai <= sons - 1 && pid - pid_pai  > 0)
        return 1;
    else
        return 0;
}

int main()
{
    int cont = 0,pid_filho_anterior,status, d, i, pid_filho_atual = getpid(),pid;
    
    for (d = 0; d < 4; d++)
    {
        if ((pid = fork()) == 0)
        {
            kill(getpid(),SIGSTOP);
            for(EVER);
        }
    }
    if(pid != 0)
        for(i = 0; i < 80; i++)
        {
            {
                sleep(1);
                if (inRange(getpid(),pid_filho_atual,4)) 
                    pid_filho_atual += 1;
                else
                {
                    pid_filho_atual = getpid() + 1;
                    cont += 1;
                }
                pid_filho_anterior = pid_filho_atual - 1;

                if (!(inRange(getpid(),pid_filho_anterior,4))) 
                    pid_filho_anterior = getpid() + 4;

                printf("Contador: %d\n",cont);
                if(cont < 20)
                {
                    printf("O pai eh %d\n",getpid());
                    printf("Vo continuar o filho %d\n",pid_filho_atual);
                    kill(pid_filho_atual,SIGCONT);
                    printf("Vo parar o filho %d\n",pid_filho_anterior);
                    kill(pid_filho_anterior,SIGSTOP);
                    
                }
                else
                {
                    printf("Vo matar o filho %d\n",pid_filho_atual);
                    kill(pid_filho_atual,SIGKILL);
                }
            }
        }
    return 0;
}