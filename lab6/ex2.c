#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>


// Alunos: Lucas Ximenes Guilhon e Miguel Fagundes Vuori

union semun
{
    int val;
    struct semid_ds *buf;
    ushort *array;
};
// inicializa o valor do semáforo
int setSemValue(int semId);
// remove o semáforo
void delSemValue(int semId);
// operação P
int semaforoP(int semId);
//operação V
int semaforoV(int semId);

int main (int argc, char * argv[])
{
    int i, d, pid, *varComp, status;
    int segmento;
    int semId;

    segmento = shmget(7007, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IROTH);
    varComp = (int *)shmat(segmento, 0, 0);
    *varComp = 0;

    semId = semget (8752, 1, 0666 | IPC_CREAT);
    setSemValue(semId);


    for (d = 0; d < 3; d++)
	{
		if ((pid = fork()) == 0)
		{
            for(i = 0; i < 500; i++)
            {   
                semaforoP(semId);
                (*varComp) = (*varComp) + d + 1;
                semaforoV(semId);
                printf("pid: %d - %d\n",getpid(),(*varComp));
                usleep(300);
            }         
            exit(0);
		}
	}

    for (d = 0; d < 3; d++)
        waitpid(-1, &status, 0);

    delSemValue(semId);

    shmdt(varComp);
    shmctl(segmento, IPC_RMID, 0);

    return 0;
}

int setSemValue(int semId)
{
    union semun semUnion;
    semUnion.val = 1;
    return semctl(semId, 0, SETVAL, semUnion);
}
void delSemValue(int semId)
{
    union semun semUnion;
    semctl(semId, 0, IPC_RMID, semUnion);
}
int semaforoP(int semId)
{
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = -1;
    semB.sem_flg = SEM_UNDO;
    semop(semId, &semB, 1);
    return 0;
}
int semaforoV(int semId)
{
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = 1;
    semB.sem_flg = SEM_UNDO;
    semop(semId, &semB, 1);
    return 0;
}