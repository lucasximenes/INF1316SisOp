#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct no{
    No* proximo;
    int val;
};

struct fila{
    int tamanho;
    No* cabeca;
    No* corrente;
    No* fim;
};

Fila* criaFila(){
    Fila *novaFila;
    novaFila = (Fila*)malloc(sizeof(Fila));
    if (novaFila == NULL){
        printf("\n Erro ao criar nova fila!! \n");
        exit(1);
    }
    return novaFila;
}

void insereFila(Fila* fila, int elem)
{
    No* novoNo;
    novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("\n Erro ao criar novo nó \n");
        exit(1);
    }

    if (fila->fim == NULL)
    {
        fila->cabeca = novoNo;
        fila->fim = novoNo ;
    } 
    else
    {
        fila->fim->proximo = novoNo;
        fila->fim = novoNo;
    }
    (fila->tamanho)++;
} 

int filaRetira(Fila* fila)
    
{
    No* aux;
    int elem;
    if (fila == NULL)
    {
        printf("\n Lista vazia \n");
        exit(1);
    }

    else if (fila->cabeca == NULL)
    {
        printf("\n Nao ha elemento no inicio da lista \n") ;
        exit(1);
    } 
    else
    {
        aux = fila->cabeca;
        fila->cabeca = fila->cabeca->proximo;
        elem = aux->val;
        free(aux);
        (fila->tamanho)--;
        return elem;
    }
}

void liberaFila(Fila* fila){
    No* aux;
    if(fila == NULL)
        return;
    else if(fila->cabeca == NULL) {
        fila->tamanho = 0;
        fila->cabeca = NULL;
        fila->corrente = NULL;
        fila->fim = NULL;
        free(fila);
        return;
    }
    while (fila->cabeca != NULL){
        filaRetira(fila);
    }
    fila->tamanho = 0;
    fila->cabeca = NULL;
    fila->corrente = NULL;
    fila->fim = NULL;
    free(fila);
}
