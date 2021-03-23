#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
    int status;
    if (fork() != 0)
    {
        char *args[]={"ls",NULL}; 
        execvp(args[0],args);
        waitpid(-1, &status, 0);
    }
    else
    {
        if (fork() != 0)
        {   
            char *args[]={"./meuecho","Testando meu ECHO",NULL}; 
            execvp(args[0],args);
            waitpid(-1, &status, 0);
        }
        else
        {
            char *args[]={"./bomdia",NULL}; 
            execvp(args[0],args);
        }
    }
    return 0;
}
