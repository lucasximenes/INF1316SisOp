#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 513

int main()
{

    int segmento, i, d;
    int *V;
    int status;

    segmento = shmget(7000, sizeof(int) * 4000, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IROTH);
    V = (int *)shmat(segmento, 0, 0);

    printf("Iniciando criacao do vetor aleatorio\n");
    for (i = 0; i < 4000; i++)
    {
        V[i] = rand() % 1000;
        if (V[i] == KEY)
            printf("chave colocada no indice %d\n", i);
    }

    for (d = 0; d < 4; d++)
    {
        if (fork() == 0)
        {
            printf("Comeca filho buscando de %d ate %d\n", d * 1000, (d + 1) * 1000);
            for (i = d * 1000; i < ((d + 1) * 1000); i++)
            {
                if (V[i] == KEY)
                {
                    printf("Chave achada no indice %d, PID = (%d)\n", i, getpid());
                }
                else
                {
                    printf("Procurando chave no indice %d, PID = (%d)\n", i, getpid());
                }
            }
            exit(0);
        }
    }

    for (d = 0; d < 4; d++)
        waitpid(-1, &status, 0);

    shmdt(V);
    shmctl(segmento, IPC_RMID, 0);
    return 0;
}