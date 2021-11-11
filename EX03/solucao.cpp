/*
    Solução para o beecrowd 1148 -> https://www.beecrowd.com.br/judge/pt/problems/view/1148
    Professor: Wladmir Cardoso Brandão
    Matéria: Laboratório de Projeto de Algoritmos
    Aluno: Lucas Santiago de Oliveira
    Matrícula: 650888
    Complexidade do algoritmo: O(n²) -> pois usa Djikstra para solução do problema
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdbool>
#include <limits>

//#define INF std::numeric_limits<int>::infinity();
#define INF 0x3f3f3f3f

typedef std::vector<std::vector<int>> matriz;

class Grafos {
    private:
        size_t vertices;
        matriz matrizAdjacente;

    public:
        Grafos(size_t vertices) {
            this->vertices = vertices;
            this->matrizAdjacente = matriz(this->vertices, std::vector<int>(vertices, INF));
        }

        void adicionarAresta(int v1, int v2, int tempo) {
            if (this->matrizAdjacente[v2][v1] != INF) {
                this->matrizAdjacente[v1][v2] = 0;
                this->matrizAdjacente[v2][v1] = 0;
            
            } else this->matrizAdjacente[v1][v2] = tempo;
        } 

        int minPathCost(int origin, int destination) {
            std::vector<int> custo;     
            std::vector<bool> visitados;

            visitados = std::vector<bool>(this->vertices,false); 
            custo   = std::vector<int>(this->vertices,INF);    
            
            custo[origin] = 0;
            
            while(true) {
                // vertex com menor peso
                int min_tempo_vertex;
                // vertex com menor peso
                int min_custo = INF;

                for(int i = 0; i < this->vertices; i++)
                    if(visitados[i] == false && min_custo > custo[i])
                        min_tempo_vertex = i, min_custo = custo[min_tempo_vertex];

                // INF quer dizer que o algoritmo acabou
                if(min_custo == INF) 
                    goto RETURN_PATH_MINIMUN_PATH;

                visitados[min_tempo_vertex] = true;     
                
                for(int i = 0; i < this->vertices; i++){
                    int travel_tempo = custo[min_tempo_vertex] + this->matrizAdjacente[min_tempo_vertex][i];
                    if(custo[i] > travel_tempo) custo[i] = travel_tempo;
                
                }
            }

            // Retornando o custo da viagem
RETURN_PATH_MINIMUN_PATH:   
            return custo[destination];
        }

};

int main() {
    int vertices, arestas;
    std::cin >> vertices >> arestas;

    while(vertices != 0) {     
        Grafos g(vertices);

        int v1,v2, tempo;
        for (int i = 0; i < arestas ; i++) {
            std::cin >> v1 >> v2 >> tempo;

            g.adicionarAresta(--v1,--v2,tempo);
        }

        int pesquisas;
        std::cin >> pesquisas;

        int origin, destination, minimum_cost;
        for (int i = 0 ; i < pesquisas; i++) {
            std::cin >> origin >> destination;

            minimum_cost = g.minPathCost(--origin,--destination);
            if (minimum_cost < INF) 
                std::cout << minimum_cost << std::endl;
            else 
                std::cout << "Nao e possivel entregar a carta" << std::endl;
        }

        std::cout << std::endl;
        std::cin >> vertices >> arestas;
    }

	return 0;
}