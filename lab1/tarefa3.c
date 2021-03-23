#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 

int main(void){
    int i, j, status;
    char *args[][3] = {{"./bomdia", NULL}, {"./meuecho", "Testando meuecho", NULL}, {"ls", NULL}};
    for (j = 0; j < 3; j++){
        if (fork() == 0)
            execvp(args[j][0], args[j]);
    }
    for (i = 0; i < 3; i++)
        waitpid(-1, &status, 0);
    return 0;
}