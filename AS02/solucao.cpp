/*
    Lucas Santiago de Oliveira - 650888
    Complexidade: O(n) -> n sendo o numero de digitos da entrada
*/

#include <stdio.h>
#include <string.h>

// Numero de LEDs necessarios para escrevem cada numero
#define LED0 6
#define LED1 2
#define LED2 5
#define LED3 5
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 3
#define LED8 7
#define LED9 6

// Numero de LEDs necessarios para escrever um numero em um Display de 7 segmentos
int numDisplaysNecessarios(char numero) {    
    switch (numero) {
        case '0':
            return LED0;

        case '1':
            return LED1;
        
        case '2':
            return LED2;

        case '3':
            return LED3;

        case '4':
            return LED4;

        case '5':
            return LED5;

        case '6':
            return LED6;

        case '7':
            return LED7;

        case '8':
            return LED8;

        case '9':
            return LED9;
        
        default:
            // Caso algum char seja diferente de um numero, retorne erro
            return -1;
    }
}

int main() {
    short numCasos;              // Numero de casos -> 1 <= N <= 1000
    char numeroDisplayLED[100];  // Tamanho da entrada -> 1 <= N <= 10^(100)
    scanf("%hd", &numCasos);

    while(numCasos != 0) {
        scanf("%s", numeroDisplayLED);

        int resultado = 0;
        for(int i = 0; i < strlen(numeroDisplayLED); i++) 
            resultado += numDisplaysNecessarios(numeroDisplayLED[i]);

        printf("%d leds\n", resultado);

        numCasos--;
    }

    return 0;
}