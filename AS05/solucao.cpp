/*
    Solução para o urijudge 1082 -> https://www.urionlinejudge.com.br/judge/pt/problems/view/1082
    Professor: Wladmir Cardoso Brandão
    Matéria: Laboratório de Projeto de Algoritmos
    Aluno: Lucas Santiago de Oliveira
    Matrícula: 650888
    Complexidade do algoritmo: O(V^2) no pior caso, deslocando duas vezes  
*/

#include <vector>
#include <cstdint>
#include <array> 
#include <unistd.h>
#include <iostream>
#include <algorithm>

// Classe de grafos
class Graph {
public:
    uint32_t numVertices;
    uint32_t numEdges;

    // Lista de adjacencia 
    std::vector<std::vector<uint32_t>> adj;

    // Iniciar grafo com 'v' numero de vertices
    Graph(uint32_t v) {    
        this->numEdges = this->numVertices = 0;
        for(int i =0 ; i < v; i++) addVertex();
    }

    // Adicionar vertice na lista de adjacencia
    void addAdj(uint32_t first, uint32_t last) {
        std::vector<uint32_t> *it = &this->adj.at(first);
        it->push_back(last);            
    }

    // Adicionar aresta ao grafo
    bool addEdge(uint32_t first, uint32_t last) {
        bool result = false; // variavel de resultado da operacao

        //Se algum dos vertices nao existir no grafo
        if(first < this->numVertices && last < this->numVertices) {
            // Adicionar ao contador 
            this->numEdges++;
            
            // Adicionar vertices a lista de adjacencia
            this->addAdj(first, last);
            this->addAdj(last, first);

            result = true;
        }

        return result;
    }

    // Adicionar nova vertice
    void addVertex() {
        this->numVertices++;
        std::vector<uint32_t> it;
        this->adj.push_back(it);
    }

    int numberOfComponents() {
        int num = 0;

        // Iniciando uma variavel para marcar vertices visitadas como falso
        bool* visited = new bool[this->numVertices];
        for(int i = 0; i < this->numVertices; i++)
            visited[i] = false;
    
        //Visitar todas as vertices
        for (int v = 0; v < this->numVertices; v++) {
            if (!visited[v]) {
                // Vetor contendo todos os vertexes já passados pelo dfs
                std::vector<char> vertexes = this->dfs(v, visited);

                // Ordenar os vértices resultantes do dfs
                std::sort(vertexes.begin(), vertexes.end());
                for(int j = 0; j < vertexes.size(); j++) 
                    std::cout << vertexes.at(j) << ",";
                
                num++;
                std::cout << std::endl; // dar espacamento
            }
        }

        // Limpar os arranjos da memória
        delete visited;
        return num;
    }

    // Depth First Search
    std::vector<char> dfs(int vert, bool *visited) {
        // Marcar vertice como visitado
        visited[vert] = true;
        std::vector<char> saida;
        
        // Inserindo o primeiro elemento no vetor ele já está sendo visitado
        saida.push_back((char) vert); 

        // Deslocar os vizinhos
        std::vector<uint32_t> adjVertex = this->adj.at(vert); 
        for (int i = 0 ; i < adjVertex.size(); i++)
            // Visitar os visinhos do vértice
            if (!visited[adjVertex.at(i)]) {
                // Salvar vizinhos visitados
                auto tmp = dfs(adjVertex.at(i), visited);
                for(int j = 0; j < tmp.size(); j++) 
                    saida.push_back(tmp.at(j));
            }

        return saida;
    }
};      

// Pegando as entradas e escrevendo a resolução do problema 1082 do urijudge
int main(int argc, char **argv) {
    int n;
    std::cin >> n;
    std::cin.ignore();
    
    // Varíaveis que serão usados no programa, declaradas aqui para serem sobreescritas durante execução
    // sem precisarem serem reinstanciadas
    int v,e;
    char v1,v2;
    for(int i = 1 ; i != n; i++) {
        // Criando grafo
        std::cin >> v >> e;
        std::cin.ignore();

        Graph* graph = new Graph(v);
        for(int j = 0 ; j < e; j++) {
            // Fazer leitura da aresta 'j' do grafo
            std::cin >> v1 >> v2;
            std::cin.ignore();

            // Adicionar vertice ao grafo como um int
            graph->addEdge(v1 - 'a', v2 - 'a');
        }

        // Imprimindo o resultado
        std::cout << "Case #" << i << ":" << std::endl;
        int num = graph->numberOfComponents();
        std::cout << num << " connected components\n" << std::endl;

        delete graph;  // Limpar o grafo da memória
    }
}