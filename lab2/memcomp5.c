#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 513

int main(){

    int segmento,i,d;
    int *V;
    segmento = shmget(7000, sizeof(int) * 4000, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IROTH);
    V = (int *) shmat (segmento,0,0);

    for(i = 0; i < 4000; i++){
        V[i] = rand() % 1000;
        if(V[i] == KEY)
            printf("chave existe\n");
    }

    for(d = 0; d < 4; d++){
        if(fork() == 0){
            for(i = d * 1000; i < ((d + 1)*1000); i++){
                if(V[i] == KEY){
                    printf("Chave achada no indice %d\n", i);
                }
            }
            exit(0);
        }

        
    }

    for (d = 0; d < 4; d++)
            wait(NULL);


    shmctl(segmento, IPC_RMID, 0);
}