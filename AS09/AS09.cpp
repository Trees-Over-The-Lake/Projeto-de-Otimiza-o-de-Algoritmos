/*
    Solução para o urijudge 1517 -> https://www.urionlinejudge.com.br/judge/en/problems/view/1517
    Professor: Wladmir Cardoso Brandão
    Matéria: Laboratório de Projeto de Algoritmos
    Aluno: Lucas Santiago de Oliveira
    Matrícula: 650888
    Complexidade do algoritmo: O(n^2) -> Sendo n o tamanho da entrada, pois todo o vetor sera deslocado inteiramente
	para cada elemento dentro dele
*/

#include <iostream>

struct Maca { int pos_x, pos_y, tempo, quant; };           // Estrutura para armazenar todos os dados sobre as macas
inline bool resolverMacas(Maca macas[1010], int i, int j); // Efetuar operações para resolver efetivamente o problema

int main (){
 	int N = 0, M = 0, K = 0, i = 0, j = 0, posicao = 0, maximo = 0;
 	Maca macas[1010];
	
	std::cin >> N >> M >> K;

 	while (N != 0){
		int x, y, tempo;

		for (i = 1; i <= K; i++){
			std::cin >> x >> y >> tempo;

			macas[i].pos_x = x;
			macas[i].pos_y = y;
			macas[i].tempo = tempo;
		}

		std::cin >> x >> y;
		macas[0].pos_x = x;
		macas[0].pos_y = y;
		macas[0].tempo = 0;

		for (i = K; i >= 0; i--){
			posicao = i;
			macas[posicao].quant = 1;

			maximo = 0;
			for(j = posicao+1; j <= K; j++)
				if (resolverMacas(macas, posicao, j) && macas[j].quant > maximo)
					maximo = macas[j].quant;

			if (maximo != 0) macas[posicao].quant = 1 + maximo;
		}

		std::cout << macas[0].quant - 1 << "\n";

		std::cin >> N >> M >> K;
	}

	return 0;
}

// Efetuar operações para resolver efetivamente o problema
inline bool resolverMacas(Maca macas[1010], int i, int j){
	int delta_x =  abs(macas[i].pos_x - macas[j].pos_x);
	int delta_y =  abs(macas[i].pos_y - macas[j].pos_y);
	int delta   =  delta_x > delta_y ? delta_x : delta_y;
	int teta    =  macas[j].tempo - macas[i].tempo;

	if (delta <= teta)
		return true;

	return false;
}