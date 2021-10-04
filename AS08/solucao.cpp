#include <iostream>

int bubblesort(int *vetor, int size) {
    int numMovimentacoes = 0;
    int aux; // Variável auxiliar para facilitar a swap de elementos

    for(int i = 0; i < size-1; i++) {
        for(int j = 0; j < size-i-1; j++) {
            if(vetor[j] > vetor[j+1]) {
                numMovimentacoes++;

                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }

    // for(int i = 0; i < size; i++) {
    //     std::cout << vetor[i];
    // }
    // std::cout << "\n";

    return numMovimentacoes;
}

int main(int argc, char **argv) {
    short entrada;
    std::cin >> entrada;

    int *valores = new int[entrada];
    int tamanhoVetor = 0;    

    while(entrada != 0) {
        // Só recriar o vetor na memória se o novo vetor precisar ser maior que o anterior
        if(tamanhoVetor < entrada) {
            tamanhoVetor = entrada;
            valores = new int[tamanhoVetor];
        
        } else
            tamanhoVetor = entrada; 

        for(int i = 0; i < entrada; i++) {
            std::cin >> valores[i];
        }

        if(bubblesort(valores, entrada) % 2) 
            std::cout << "Marcelo" << std::endl;

        else 
            std::cout << "Carlos" << std::endl;

        std::cin >> entrada;
    }

    return 0;
}