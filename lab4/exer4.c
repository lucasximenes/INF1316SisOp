#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void zeroHandler(int sinal);

int main(int argc, char *argv[])
{
    void (*p)(int);
    float num1, num2, sum, sub, mul, div;
    p = signal(SIGFPE, zeroHandler);
    num1 = atof(argv[1]);
    num2 = atof(argv[2]);
    sum = num1 + num2;
    printf("%.3f + %.3f =  %.3f\n", num1, num2, sum);
    sub = num1 - num2;
    printf("%.3f - %.3f =  %.3f\n", num1, num2, sub);
    mul = num1 * num2;
    printf("%.3f * %.3f =  %.3f\n", num1, num2, mul);
    if ((int)num2 == 0)
    {
        div = (int)num1 / (int)num2;
        printf("%.3f / %.3f =  %.3f\n", num1, num2, div);
    }
    else
    {
        div = num1 / num2;
        printf("%.3f / %.3f =  %.3f\n", num1, num2, div);
    }
    return 0;
}

void zeroHandler(int sinal)
{
    printf("Você tentou dividir por 0!!!!!!, sig:(%d)\n", sinal);
    exit(0);
}