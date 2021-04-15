#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    float num1, num2;
    num1 = atof(argv[1]);
    num2 = atof(argv[2]);
    printf("%.3f + %.3f =  %.3f\n", num1, num2, num1 + num2);
    printf("%.3f - %.3f =  %.3f\n", num1, num2, num1 - num2);
    printf("%.3f * %.3f =  %.3f\n", num1, num2, num1 * num2);
    printf("%.3f / %.3f =  %.3f\n", num1, num2, num1 / num2);
    return 0;
}