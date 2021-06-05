#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct pagina
{
    int R;
    int M;
    short emMemoria;
    time_t ultimoAcesso;
};

typedef struct pagina Pagina;

int main (int argc, char * argv[]){
    int tamPag, tamMem, tempo = 0, res = 0;
    FILE * file;
    char * rw, * algoritmo;
    unsigned int addr, page, bits, mAddr;
    int numPags, numQuadros, *memoria;
    time_t tinicial = time(NULL);

    if(argc == 5){
        Pagina ** tabela;
        algoritmo = argv[1];
        tamPag = atoi(argv[3]);
        tamMem = atoi(argv[4]);

        if(tamPag < 8 || tamPag > 32)
        {
            printf("Tamanho da pagina deve ter o valor entre 8 e 32");
            return 0;
        }

        if(tamMem < 8 || tamMem > 32)
        {
            printf("Tamanho da memoria deve ter o valor entre 1 e 16");
            return 0;
        }
        numQuadros = (tamMem/tamPag) * 1024;
        memoria = (int *) malloc (numQuadros * sizeof(int)); // vetor que representa a memoria

        // inicializacao da memoria, -1 representa a ausencia de pagina
        for (int i = 0; i < numQuadros; i++) {
            memoria[i] = -1;
        }
        printf("\nnumquadros = %d\n", numQuadros);

        file = fopen( argv[2] , "r");
        // if (file == NULL)
        //     exit(EXIT_FAILURE);

        printf("Executando o simulador...\n");
        printf("Arquivo de entrada: %s\n", argv[2]);
        printf("Tamanho da memoria fisica: %s MB\n", argv[4]);
        printf("Tamanho das paginas: %s KB\n", argv[3]);
        printf("Algoritmo de substituição: %s\n", argv[1]);


        tamMem *= 1024; // passando de MB para KB
        bits = 0; // bits menos significativos
        mAddr = tamPag * 1024 - 1; // maximo de memoria

        while (mAddr > 0) {
            mAddr = mAddr >> 1;
            bits++;
        }

        numPags = (int)pow(2.0,(double)(32 - bits));

        printf("bits = %d\n",bits);
        printf("1 : %d , 2 : %f\n", numPags, pow(2.0,(double)(32 - bits)));

        // Cria tabela de paginas
        tabela = (Pagina **) malloc(numPags * sizeof(Pagina *));

        // Inicializa tabela
        for (int i = 0; i < numPags; i++) {
            Pagina *p = (Pagina *) malloc(sizeof(Pagina));
            tabela[i] = p;
            tabela[i]->R = 0;
            tabela[i]->M = 0;
            tabela[i]->emMemoria = 0;
            tabela[i]->ultimoAcesso = 0;
        }
        
        // leitura do log de entrada
        while ((res = fscanf(log, "%x %c ", &addr, &rw)) != EOF)
        {
            page = addr >> bits; // indice da pagina

            // caso o algoritmo seja NRU reseta as flags a cada 1000 iteracoes
            if (!strcmp(algoritmo,"LRU") && tempo % 1000)
            {
                for(int i = 0; i < numQuadros; i++)
                {
                    if(memoria[i] != -1 && (tabela[memoria[i]]->R))
                    {
                        tabela[memoria[i]]->R = 0;
                    }
                }
            }

            // a pagina nao esta na memoria
            if(!tabela[page]->emMemoria)
            {
                // chama o algoritmo de substituicao de pagina correspondente

                if(!strcmp(algoritmo,"LRU"))
                {

                }
                else if (!strcmp(algoritmo,"NRU"))
                {

                }
                else if (!strcmp(algoritmo,"2Chance"))
                {

                }

                tabela[page]->R = 1;
                if(rw == "W")
                {
                    tabela[page]->M = 1;
                }
            }

            tempo++;

            
        }

        // liberacao da memoria dinamica
        for (int i = 0; i < numPags; i++) {
            free(tabela[i]);
        }
        free(tabela);
        free(memoria);

    }
    else{
        printf("\nNúmero de argumentos passados diferente de 5, terminando execução...\n");
    }
    return 0;
}