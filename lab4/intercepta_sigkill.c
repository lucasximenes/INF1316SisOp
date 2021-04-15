#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define EVER ;;

void killHandler(int sinal);
int main (void)
{
void (*p)(int);// ponteiro para função que recebe int como parâmetro
p = signal(SIGKILL, killHandler);
printf("Pid = %d\n", getpid());
printf("Endereco do manipulador anterior %p\n", p);
kill(getpid(),SIGKILL);
for(EVER);
}
void killHandler(int sinal)
{
printf("Vamos matar o processo (%d)", sinal);
}