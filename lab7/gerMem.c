#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct gerMem
{
    int R;
    int M;
    int ultimoAcesso;
};


int main (int argc, char * argv[]){
    int tamPag, tamMem, time = 0;
    FILE * file;
    char * rw;
    unsigned int addr, page;

    if(argc == 5){
        tamPag = argv[3];
        tamMem = argv[4];

        file = fopen( argv[2] , "r");
        if (file == NULL)
            exit(EXIT_FAILURE);

        printf("%s %s %s %s %s\n", argv[0],argv[1],argv[2],argv[3],argv[4]);
        printf("Executando o simulador...\n");

        while (fscanf(file, "%x %c ", &addr, &rw))
        {
            page = addr >> int((pow(double(tamPag),double(0.5)) + 10));
        }
        

    }
    else{
        printf("Número de argumentos passados diferente de 5, terminando execução...");
    }
    return 0;
}