#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "fila.h"

struct pagina
{
    short R;
    short M;
    short emMemoria;
    unsigned int endereco;
    unsigned int numeroAcessos;
};

typedef struct pagina Pagina;

int main(int argc, char *argv[])
{
    int tamPag, tamMem, tempo = 0, res = 0;
    FILE *file;
    char rw, *algoritmo;
    unsigned int addr, page, bits, mAddr;
    int numPags, numQuadros, *memoria;
    int n_pageFaults = 0;
    Fila *memFila;
    unsigned int paginasEscritas = 0;
    clock_t start, stop;

    if (argc == 5)
    {
        Pagina **tabela;
        algoritmo = argv[1];
        tamPag = atoi(argv[3]);
        tamMem = atoi(argv[4]);

        if (tamPag < 8 || tamPag > 32)
        {
            printf("Tamanho da pagina deve ter o valor entre 8 e 32");
            return 0;
        }

        if (tamMem < 8 || tamMem > 32)
        {
            printf("Tamanho da memoria deve ter o valor entre 1 e 16");
            return 0;
        }
        numQuadros = (tamMem / tamPag) * 1024;
        memoria = (int *)malloc(numQuadros * sizeof(int)); // vetor que representa a memoria
        memFila = criaFila();
        

        // inicializacao da memoria, -1 representa a ausencia de pagina
        for (int i = 0; i < numQuadros; i++)
        {
            memoria[i] = -1;
            insereFila(memFila, -1);
        }
        // printf("\nnumquadros = %d\n", numQuadros);

        file = fopen(argv[2], "r");
        if (file == NULL)
            exit(EXIT_FAILURE);

        printf("Executando o simulador...\n");
        printf("Arquivo de entrada: %s\n", argv[2]);
        printf("Tamanho da memoria fisica: %s MB\n", argv[4]);
        printf("Tamanho das paginas: %s KB\n", argv[3]);
        printf("Algoritmo de substituição: %s\n", argv[1]);

        tamMem *= 1024;            // passando de MB para KB
        bits = 0;                  // bits menos significativos
        mAddr = tamPag * 1024 - 1; // maximo de memoria

        while (mAddr > 0)
        {
            mAddr = mAddr >> 1;
            bits++;
        }

        numPags = (int)pow(2.0, (double)(32 - bits));

        // printf("bits = %d\n", bits);
        // printf("1 : %d , 2 : %f\n", numPags, pow(2.0, (double)(32 - bits)));

        // Cria tabela de paginas
        tabela = (Pagina **)malloc(numPags * sizeof(Pagina *));

        // Inicializa tabela
        for (int i = 0; i < numPags; i++)
        {
            Pagina *p = (Pagina *)malloc(sizeof(Pagina));
            tabela[i] = p;
            tabela[i]->R = 0;
            tabela[i]->M = 0;
            tabela[i]->emMemoria = 0;
            tabela[i]->numeroAcessos = 0;
        }

        // leitura do log de entrada
        start = clock();
        while ((res = fscanf(file, "%x %c ", &addr, &rw)) != EOF)
        {
            int novoEndereco = 0;
            page = addr >> bits; // indice da pagina

            // caso o algoritmo seja NRU reseta as flags a cada 1000 iteracoes
            if (!strcmp(algoritmo, "NRU") && tempo % 1000)
            {
                for (int i = 0; i < numQuadros; i++)
                {
                    if (memoria[i] != -1 && tabela[memoria[i]]->R == 1)
                    {
                        tabela[memoria[i]]->R = 0;
                    }
                }
            }

            // a pagina nao esta na memoria
            if (!tabela[page]->emMemoria)
            {
                n_pageFaults++;

                //testa para ver se tem espaço na memória para a pagina
                novoEndereco = 0; // novo endereço da página na memória
                short achou = 0;

                
                if(!strcmp(algoritmo, "2Chance"))
                {
                    memFila->corrente = memFila->cabeca;

                    for (int i = 0; i < numQuadros && achou == 0; i++)
                    {
                        // achou lugar vazio pra nova página na memória
                        if (memoria[memFila->corrente->val] == -1)
                        {
                            novoEndereco = i;
                            achou = 1;
                        }
                        memFila->corrente = memFila->corrente->proximo;
                    }
                }
                else
                {
                    for (int i = 0; i < numQuadros && achou == 0; i++)
                    {
                        // achou lugar vazio pra nova página na memória
                        if (memoria[i] == -1)
                        {
                            novoEndereco = i;
                            achou = 1;
                        }
                    }
                }
                

                // chama o algoritmo de substituicao de pagina correspondente
                if (achou == 0)
                {
                    if (!strcmp(algoritmo, "LFU"))
                    {
                        int menorAcessos = 0;
                        for (int i = numQuadros - 1; i >= 0; i--)
                        {
                            if (tabela[memoria[i]]->numeroAcessos < menorAcessos)
                            {
                                menorAcessos = tabela[memoria[i]]->numeroAcessos;
                                novoEndereco = i;
                            }
                        }
                    }
                    else if (!strcmp(algoritmo, "NRU"))
                    {

                        short substituiu = 0;

                        for (int i = 0; i < numQuadros && substituiu == 0; i++)
                        {
                            if (tabela[memoria[i]]->R == 0 && tabela[memoria[i]]->M == 0)
                            {
                                novoEndereco = i;
                                substituiu = 1;
                            }
                        }

                        for (int i = 0; i < numQuadros && substituiu == 0; i++)
                        {
                            if (tabela[memoria[i]]->M == 1)
                            {
                                novoEndereco = i;
                                substituiu = 1;
                            }
                        }

                        for (int i = 0; i < numQuadros && substituiu == 0; i++)
                        {
                            if (tabela[memoria[i]]->R == 1)
                            {

                                novoEndereco = i;
                                substituiu = 1;
                            }
                        }
                    }
                    else if (!strcmp(algoritmo, "2Chance"))
                    {
                        short substituiu = 0;
                        int shift = 0, bShift = 0, valorInicial;
                        novoEndereco = 0;
                        memFila->corrente = memFila->cabeca;

                        for (int i = 0; i < numQuadros && substituiu; i++)
                        {
                            if (tabela[memFila->corrente->val]->R == 0)
                            {
                                substituiu = 1;
                                novoEndereco = i;
                            }
                            else
                            {
                                tabela[memFila->corrente->val]->R = 0;
                                memFila->corrente = memFila->corrente->proximo;
                                shift++;
                                bShift = 1;

                            }
                        }

                        // shifta a fila de memoria
                        if(bShift)
                        {
                            for(int i = 0; i < shift; i++)
                            {
                                int val = filaRetira();
                                insereFila(memFila, val);
                            }
                            
                        }
                        
                    }
                }
            }

            if (memoria[novoEndereco] != -1)
            { 
                tabela[memoria[novoEndereco]]->emMemoria = 0;
                if (tabela[memoria[novoEndereco]]->M == 1)
                {
                    tabela[memoria[novoEndereco]]->R = 0;
                    tabela[memoria[novoEndereco]]->M = 0;
                    paginasEscritas++;
                }
            }

            tabela[page]->emMemoria = 1;
            tabela[page]->endereco = novoEndereco;

            memoria[novoEndereco] = page;

            tabela[page]->R = 1;
            if (rw == 'W')
            {
                tabela[page]->M = 1;
            }
            tabela[page]->numeroAcessos++;
            tempo++;
        }
        stop = clock();
        // liberacao da memoria dinamica
        for (int i = 0; i < numPags; i++)
        {
            free(tabela[i]);
        }
        free(tabela);
        free(memoria);
        printf("Número de Faltas de Páginas: %d\n", n_pageFaults);
        printf("Número de Páginas Escritas: %d\n", paginasEscritas);
        printf("Tempo de execucao: %f\n", (double)(stop - start) / CLOCKS_PER_SEC);
    }
    else
    {
        printf("\nNúmero de argumentos passados diferente de 5, terminando execução...\n");
    }
    return 0;
}