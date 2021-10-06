/*
    Aluno: Lucas Santiago de Oliveira
    Complexidade de memória: O(n) -> n sendo o número de dias
*/

#include <iostream>

// Metodo para conter as bacterias daquele dia
uint64_t numBacterias(uint64_t quantBacteriasIniciais[], uint64_t numDias) {
    // Resultado da funcao salvo em uma variavel unsigned int de criacao rapida naquele hardware
    uint64_t bacterias[numDias];
    // Resultado final
    uint64_t soma = 0;

    // Passando a limpo o veotr
    for (uint64_t i = 0; i < 4; i++) {
        bacterias[i] = quantBacteriasIniciais[i];
        soma += bacterias[i];
    }

    for(uint64_t i = 4; i < numDias; i++) {
        bacterias[i] = (soma*2) - bacterias[i - 4]; 
        soma = bacterias[i];
    }

    return bacterias[numDias - 1];
}

int main() {
    // Numero de dias
    uint64_t numDias;
    std::cin >> numDias;
    std::cin.ignore();

    // Qauntidade de colonias de bacterias no dia inicial
    uint64_t quantInicialBacterias[4];
    while(numDias != 0) {
        for(uint64_t i = 0; i < 4; i++) {
            std::cin >> quantInicialBacterias[i];
        }
        std::cin.ignore();

        std::cout << numBacterias(quantInicialBacterias, numDias) << std::endl;

        std::cin >> numDias;
        std::cin.ignore();
    }

    return 0;
}
