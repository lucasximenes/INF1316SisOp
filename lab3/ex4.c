#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define NUM_THREADS 4

// Alunos: Lucas Ximenes Guilhon e Miguel Fagundes Vuori

int V[4000];
int greatest = -1;

void *busca(void *threadid)
{
    int i, *id = threadid;

    printf("Executando busca, threadid -> %d", *id);
    for (i = (*id) * 1000; i < (((*id) + 1) * 1000); i++)
    {
        if (V[i] > greatest)
        {
            printf("\nMaior valor ate agora == %d foi achado no indice %d, TID = (%d)\n", V[i], i, *id);
            greatest = V[i];
        }
    }
    return 0;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int t, maior_comp = -1;
    for (int cont = 0; cont < 4000; cont++)
    {
        V[cont] = rand() % 1000;
        if (V[cont] > maior_comp) maior_comp = V[cont]; 
    }
    printf("\nMaior valor do vetor é %d\n", maior_comp);

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Creating thread busca, threadId ==  %d\n", t);
        pthread_create(&threads[t], NULL, busca, (void*)t);
    }
    printf("oi\n");
    for (t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t], NULL); 
    return 0;
}