typedef struct no No;
typedef struct fila Fila;

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

Fila* criaFila();
void liberaFila();
void liberaFila();
void insereFila();
int filaRetira();