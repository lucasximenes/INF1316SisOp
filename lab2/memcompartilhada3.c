#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Participantes: Lucas Ximenes Guilhon e Miguel Vuori

int main(int argc, char *argv[])
{
    int segmento;
    char *msg;
    // aloca a memória compartilhada    
    segmento = shmget(7000, sizeof(char) * 256, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IROTH);
    // associa a memória compartilhada ao processo
    p = (char *)shmat(segmento, 0, 0); // comparar o retorno com -1
    //scanf("%[^\n]%*c", msg);
    strcpy(msg, argv[1]);
    printf("%s\n",msg);
    // libera a memória compartilhada do processo
    shmdt(msg);
    return 0;
}