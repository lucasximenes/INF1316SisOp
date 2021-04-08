#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 4
#define KEY 513

// Alunos: Lucas Ximenes Guilhon e Miguel Fagundes Vuori

typedef struct
{
    int *vetor;
    int particao;
} dados;

void *ProcuraChave(void *foo)
{
    int i;
    dados *vals = foo;
    for (i = vals->particao * 1000; i < ((vals->particao + 1) * 1000); i++)
    {
        if (vals->vetor[i] == KEY)
        {
            printf("Chave achada no indice %d, thread = %d\n", i, vals->particao);
        }
        else
        {
            printf("Procurando chave no indice %d, thread = %d\n", i, vals->particao);
        }
    }
    free(foo);
    return 0;
}
int main()
{
    pthread_t threads[NUM_THREADS];
    int t, *V;
    V = (int *)malloc(sizeof(int) * 4000);
    for (t = 0; t < 4000; t++)
    {
        V[t] = rand() % 1000;
        if (V[t] == KEY)
            printf("chave criada no indice %d\n", t);
    }
    for (t = 0; t < NUM_THREADS; t++)
    {
        dados *params;
        params = (dados *)malloc(sizeof(dados));
        params->particao = t;
        params->vetor = V;
        printf("Creating thread %d\n", t);
        pthread_create(&threads[t], NULL, ProcuraChave, params);
    }
    for (t = 0; t < NUM_THREADS; t++)
    /* wait for all the threads to terminate*/
        pthread_join(threads[t], NULL); 
    free(V);
    return 0;
}