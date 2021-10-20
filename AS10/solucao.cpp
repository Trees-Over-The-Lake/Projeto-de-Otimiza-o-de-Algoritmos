/*
    Solução para o urijudge 1021 -> https://www.urionlinejudge.com.br/judge/en/problems/view/1021
    Professor: Wladmir Cardoso Brandão
    Matéria: Laboratório de Projeto de Algoritmos
    Aluno: Lucas Santiago de Oliveira
    Matrícula: 650888
    Complexidade do algoritmo: O(n) -> Sendo n o tamanho da entrada, pois todo o vetor será deslocado apenas 1 vez
*/

#include <iostream>

const double valores[] = {100.0, 50.0, 20.0, 10.0, 5.0, 2.0, 1.0, 0.5, 0.25, 0.1, 0.05, 0.01};

void contarNotasEMoedas(float valor, int *numNotas) {
    int i = 0;

    // Removendo a parte da precisão que não é importante
    while(valor >= 0.01) {
        if(valores[i] <= valor) {
            valor -= valores[i];
            numNotas[i] += 1;

        } else 
            i++;

    }

    // Verificando
    if((int)(valor*1000) % 10 != 0) numNotas[11]++;
}


int main() {
    double entrada;
    std::cin >> entrada;
    std::cin.ignore();

    int numNotas[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    contarNotasEMoedas(entrada, numNotas);

    // Escrevendo na tela os resultados
    std::cout << "NOTAS:" << std::endl;
    std::cout << numNotas[0] << " nota(s) de R$ 100.00" << std::endl;
    std::cout << numNotas[1] << " nota(s) de R$ 50.00" << std::endl;
    std::cout << numNotas[2] << " nota(s) de R$ 20.00" << std::endl;
    std::cout << numNotas[3] << " nota(s) de R$ 10.00" << std::endl;
    std::cout << numNotas[4] << " nota(s) de R$ 5.00" << std::endl;
    std::cout << numNotas[5] << " nota(s) de R$ 2.00" << std::endl;

    std::cout << "MOEDAS:" << std::endl;
    std::cout << numNotas[6] << " moeda(s) de R$ 1.00" << std::endl;
    std::cout << numNotas[7] << " moeda(s) de R$ 0.50" << std::endl;
    std::cout << numNotas[8] << " moeda(s) de R$ 0.25" << std::endl;
    std::cout << numNotas[9] << " moeda(s) de R$ 0.10" << std::endl;
    std::cout << numNotas[10] << " moeda(s) de R$ 0.05" << std::endl;
    std::cout << numNotas[11] << " moeda(s) de R$ 0.01" << std::endl;

    return 0;
}