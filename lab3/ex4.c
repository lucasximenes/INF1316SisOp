#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define NUM_THREADS 4

// Alunos: Lucas Ximenes Guilhon e Miguel Fagundes Vuori

typedef struct
{
    int *vetor;
    int particao;
    int greatest;
} dados;

void *busca(void *foo)
{
    dados *vals = foo;
    int i, id = vals->particao;
    vals->greatest = -1;
    printf("Executando busca, threadid -> %d\n", id);
    for (i = id * 1000; i < ((id + 1) * 1000); i++)
    {
        if (vals->vetor[i] > vals->greatest)
        {
            printf("\nMaior valor ate agora == %d foi achado no indice %d, TID = (%d)\n", vals->vetor[i], i, id);
            vals->greatest = vals->vetor[i];
        }
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int t, maior_comp = -1, greatest_comp = -1, *V;
    dados res[4];
    V = (int *)malloc(sizeof(int) * 4000);
    for (int cont = 0; cont < 4000; cont++)
    {
        V[cont] = rand() % 10000;
        if (V[cont] > maior_comp) maior_comp = V[cont]; 
    }
    printf("\nMaior valor colocado no vetor é %d\n", maior_comp);

    for (t = 0; t < NUM_THREADS; t++)
    {
        res[t].particao = t;
        res[t].vetor = V;
        res[t].greatest = -1;
        printf("Creating a search thread, threadId ==  %d\n", t);
        pthread_create(&threads[t], NULL, busca, (void*) &res[t]);
    }
    
    clock_t begin = clock();
    for (t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t], NULL);

    for (t = 0; t < NUM_THREADS; t++){
        if (res[t].greatest > greatest_comp)
            greatest_comp = res[t].greatest;
    }
    printf("\nMaior valor achado no vetor foi %d\n", greatest_comp);
    free(V);
    clock_t end = clock();
    double total_t = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t );
    return 0;
}