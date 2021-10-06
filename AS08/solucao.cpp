#include <iostream>

// Swap de elements
void swap(int *a, int *b, int *numMovimentacoes) {
    int aux = *a;
    *a = *b;
    *b = aux;
    *numMovimentacoes++;
}

// Algoritmo de divisão e conquista
void mergesort(int i, int j, int a[], int aux[], int *numMovimentacoes) {
    if (j <= i) return; 

    int mid = (i + j) / 2;

    mergesort(i, mid, a, aux, numMovimentacoes);
    mergesort(mid + 1, j, a, aux, numMovimentacoes);

    int pLeft = i;
    int pRight = mid + 1;
    int k;

    for (k = i; k <= j; k++) {
        if (pLeft == mid + 1) {
            aux[k] = a[pRight];
            pRight++;
            *numMovimentacoes += mid-k;
        
        } else if (pRight == j + 1) {
            aux[k] = a[pLeft];
            pLeft++;
        
        } else if (a[pLeft] < a[pRight]) {
            aux[k] = a[pLeft];
            pLeft++;
        
        } else {
            aux[k] = a[pRight];
            pRight++;
            *numMovimentacoes += mid-k;
        
        }
    }

    for (k = i; k <= j; k++) 
        a[k] = aux[k];
        
}

// Escrever o array na tela
void printArray(int array[], int size) {
    std::cout << "Array: ";

    for (int i = 0; i < size; i++)
        std::cout << array[i] << " ";

    std::cout << std::endl;
}

int main(int argc, char **argv) {
    int entrada;
    std::cin >> entrada;

    int *valores = new int[entrada];
    int tamanhoVetor = 0;
    int numMovimentacoes;

    while (entrada != 0) {
        // Só recriar o vetor na memória se o novo vetor precisar ser maior que o anterior
        if (tamanhoVetor < entrada) {
            tamanhoVetor = entrada;
            valores = new int[tamanhoVetor];
        
        } else
            tamanhoVetor = entrada;

        for (int i = 0; i < tamanhoVetor; i++) 
            std::cin >> valores[i];
        
        
        numMovimentacoes = 0;
        int vetorAuxiliar[tamanhoVetor];
        mergesort(0, entrada-1, valores, vetorAuxiliar, &numMovimentacoes);

        if (numMovimentacoes % 2)
            std::cout << "Marcelo" << std::endl;

        else
            std::cout << "Carlos" << std::endl;


        std::cin >> entrada;
    }

    return 0;
}