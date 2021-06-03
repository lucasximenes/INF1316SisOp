#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct gerMem
{
    int R;
    int M;
    time_t last_access;
};

typedef struct gerMem GerMem;


int main (int argc, char * argv[]){
    int tamPag, tamMem, time = 0;
    FILE * file;
    char * rw;
    unsigned int addr, page;
    int numPags;

    if(argc == 5){
        GerMem* tabela;
        tamPag = atoi(argv[3]);
        tamMem = atoi(argv[4]);
        numPags = (tamMem/tamPag) * 1000;
        printf("\nnumpags = %d\n", numPags);
        // tabela = (GerMem*)malloc(sizeof(GerMem)*numPags);
        file = fopen( argv[2] , "r");
        // if (file == NULL)
        //     exit(EXIT_FAILURE);

        printf("Executando o simulador...\n");
        printf("Arquivo de entrada: %s\n", argv[2]);
        printf("Tamanho da memoria fisica: %s MB\n", argv[4]);
        printf("Tamanho das paginas: %s KB\n", argv[3]);
        printf("Algoritmo de substituição: %s\n", argv[1]);

        // while (fscanf(file, "%x %c", &addr, &rw))
        // {
        //     page = addr >> (int)(sqrt(tamPag) + 10);
        // }
        

    }
    else{
        printf("\nNúmero de argumentos passados diferente de 5, terminando execução...\n");
    }
    return 0;
}