/*
    Solução para o urijudge 1295 -> https://www.urionlinejudge.com.br/judge/pt/problems/view/1295
    Professor: Wladmir Cardoso Brandão
    Matéria: Laboratório de Projeto de Algoritmos
    Aluno: Lucas Santiago de Oliveira
    Matrícula: 650888
    Complexidade do algoritmo: O(n^2) -> Sendo n o tamanho da entrada, pois todo o vetor será deslocado
*/

#include <iostream>
#include <cstdint>
#include <cmath>
#include <iomanip>

// Calculando a distância real entre dois pontos
float distanciaEntre2Pontos(int x1, int y1, int x2, int y2) {
    // Descobrindo o triângulo retângulo
    // A hipotenusa é a distância efetiva que procuro
    int deltaY = std::abs(y2 - y1);
    int deltaX = std::abs(x2 - x1);

    // Pitágoras
    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

// Descobrindo a maior distância entre dois pontos
float distanciaDoPontoMaisProximo(std::pair<int, int> pares[], int numCasos) {
    float menorDistancia = __FLT_MAX__;
    float aux; // Variável para armazenar o valor atual

    // Testando todos com todos
    for(int i = 0; i < numCasos-2; i++) {
        for(int j = i+1; j < numCasos-1; j++) {
            // Calculando distância entre os pontos
            aux = distanciaEntre2Pontos(pares[i].first, pares[i].second, pares[j].first, pares[j].second);

            // Se o novo valor for o menor substituir
            if(aux < menorDistancia)
                menorDistancia = aux;
        }
    }

    return menorDistancia;
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    std::cin.ignore();

    while(numCasos != 0) {
        // Variável para salvar os pares
        std::pair<int, int> pares[numCasos];
        // Recebendo as numCasos entradas
        for(int i = 0; i < numCasos; i++) {
            std::cin >> pares[i].first >> pares[i].second;
            std::cin.ignore();
        }

        float resposta = distanciaDoPontoMaisProximo(pares, numCasos);

        if (resposta >= 10000)
            std::cout << "INFINITY" << std::endl;
        else
            std::cout << std::fixed << std::setprecision(4) << resposta << std::endl;

        std::cin >> numCasos;
        std::cin.ignore();
    }

    return 0;
}