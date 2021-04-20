#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define NUM_THREADS 2

// Alunos: Lucas Ximenes Guilhon e Miguel Fagundes Vuori

int var_global = 0;

void *contCrescente(void *foo)
{
    int j;
    printf("Executando contCrescente, threadid -> %d", foo);
    for (j = 1; j < 61; j++)
    {
        printf("\nN = %d\n", j);
        printf("\nvarglobal = %d, threadid -> %d\n", var_global++, foo);
        sleep(2);
    }
    return;
}

void *contDecrescente(void *foo)
{
    int j;
    printf("Executando contDecrescente, threadid -> %d", foo);
    for (j = 60; j > 0; j--)
    {
        printf("\nM = %d\n", j);
        printf("\nvarglobal = %d, threadid -> %d\n", var_global--, foo);
        sleep(1);
    }
    return;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int t;
    for (t = 0; t < NUM_THREADS; t++)
    {
        if (t == 0)
        {
            printf("Creating thread contCrescente, threadId ==  %d\n", t);
            pthread_create(&threads[t], NULL, contCrescente, (void*)t);
        }
        else{
            printf("Creating thread contDecrescente, threadId == %d\n", t);
            pthread_create(&threads[t], NULL, contDecrescente, (void*)t);
        }
    }
    for (t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t], NULL); 
    return 0;
}