#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#define EVER ;;

void intHandler(int sinal);
void quitHandler(int sinal);
int main (void)
{
void (*p)(int);// ponteiro para função que recebe int como parâmetro
p = signal(SIGINT, intHandler);
printf("Endereco do manipulador anterior %p\n", p);
p = signal(SIGQUIT, quitHandler);
printf("Endereco do manipulador anterior %p\n", p);
puts("Ctrl-C desabilitado. Use Ctrl-\\ para terminar");
printf("Ctrl-C desabilitado. Use Ctrl-\\ para terminar\n");
for(EVER);
}
void intHandler(int sinal)
{
puts ("Você pressionou Ctrl-C (%d)", sinal);
printf("Você pressionou Ctrl-C (%d)\n", sinal);
}
void quitHandler(int sinal)
{
puts ("Terminando o processo...");
printf("Terminando o processo...\n");
exit(0);
}