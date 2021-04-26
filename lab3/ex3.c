#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Alunos: Lucas Ximenes Guilhon e Miguel Fagundes Vuori

int main()
{
    int cont, d, i, *V, *greatest, aux, status,valor_comp = -1;
    int segmento, segmento2;
    segmento = shmget(7005, sizeof(int) * 4000, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IROTH);
    segmento2 = shmget(7006, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IROTH);
    
    V = (int *)shmat(segmento, 0, 0);
    greatest = (int *)shmat(segmento2, 0, 0);
    if(greatest != -1)
        *greatest = 0;
    else
        printf("erro na alocação de memoria de greatest\n");
    if(V == -1)
        printf("erro na alocação de memoria de V\n");
    
    for (cont = 0; cont < 4000; cont++)
    {
        aux = rand() % 1000;
        V[cont] = aux;
        if (V[cont] > valor_comp) valor_comp = V[cont];
    }
    printf("\nMaior valor do vetor é %d\n", valor_comp);
    for (d = 0; d < 4; d++)
    {
        if (fork() == 0)
        {
            printf("\nComeca filho buscando o maior valor entre os indices %d e %d, PID = (%d)\n", d * 1000, (d + 1) * 1000 - 1, getpid());
            for (i = d * 1000; i < ((d + 1) * 1000); i++)
            {
                if (V[i] > *greatest)
                {
                    printf("\nMaior valor ate agora == %d foi achado no indice %d, PID = (%d)\n", V[i], i, getpid());
                    *greatest = V[i];
                }
            }
            
            exit(0);
        }
    }

    clock_t begin = clock();
    for (d = 0; d < 4; d++)
        waitpid(-1, &status, 0);
    clock_t end = clock();

    printf("Ao final do programa encontramos %d para o maior valor do vetor\n",*greatest);
    shmdt(V);
    shmdt(greatest);
    shmctl(segmento,IPC_RMID,0);
    shmctl(segmento2,IPC_RMID,0);
    double total_t = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t );
    return 0;
}