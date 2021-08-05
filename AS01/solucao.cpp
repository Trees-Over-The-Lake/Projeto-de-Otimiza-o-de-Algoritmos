#include <stdio.h>

unsigned long fatorial(unsigned long entrada) {
    if(entrada != 0) entrada *= fatorial(entrada - 1);
    if (entrada == 0) return 1;
    return entrada;
}

// Soma de fatoriais
int main() {
    int fat1, fat2;
    while(scanf("%d %d", &fat1, &fat2) != EOF) {
        printf("%ld\n", fatorial(fat1) + fatorial(fat2));
    }

    return 0;
}