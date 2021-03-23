#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// Participantes: Lucas Ximenes Guilhon e Miguel Vuori

int main(int argc, char *argv[])
{
    int segmento;
    char *msg;
    // aloca a memória compartilhada, aqui como só queremos ler o que tem dentro, optei por colocar 0 no
    //tamanho
    segmento = shmget(7000, 0, 0);
    // associa a memória compartilhada ao processo
    msg = (char *)shmat(segmento, 0, 0); // comparar o retorno com -1
    printf("%s\n", msg);
    // libera a memória compartilhada do processo
    shmdt(msg);
    // libera a memória compartilhada
    shmctl(segmento, IPC_RMID, 0);
    return 0;
}