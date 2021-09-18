// Solution for uri judge 1082 -> https://www.urionlinejudge.com.br/judge/pt/problems/view/1082

//AS04: Gustavo Lopes
#include <vector>
#include <cstdint>
#include <array> 
#include <unistd.h>
#include <iostream>
#include <algorithm>

/* Complexidade: O(V^2), pois o algoritmo precisa atravessar todas as
*  vertices(V) e no pior caso, durante o DFS, ele vai precisar atravessar
*  o grafo inteiro, logo, tornando o algoritmo mais custoso
*/

// Classe de grafos
class Graph {
public:

    // Num de vertices e arestas
    uint32_t vertices;
    uint32_t edges;

    // Lista de adjacencia 
    std::vector<std::vector<uint32_t>> adj;


    // Iniciar grafo com 'v' numero de vertices
    Graph(uint32_t v) {    
        this->edges    = 0;
        this->vertices = 0;

        for(int i =0 ; i < v; i++) 
            add_vertex();
    }

    // Retornar numero de vertices
    uint32_t vertices_num() {
        return this->vertices;
    }

    // Adicionar vertice na lista de adjacencia
    void add_adj(uint32_t first, uint32_t last) {
        auto it = &this->adj.at(first); // Resgatar ponteiro para a lista na posicao 'first'

        // Inserir 'last' para a lista resgatada, como a variavel eh um 
            // ponteiro, o elemento sera atualizado na memoria
        it->push_back(last);            
    }

    // Adicionar aresta ao grafo
    bool add_edge(uint32_t first, uint32_t last) {
        bool result = false; // variavel de resultado da operacao

        //Se algum dos vertices nao existir no grafo
        if(first < this->vertices_num() && last < this->vertices_num()) {
            
            // Adicionar ao contador 
            this->edges++;
            
            // Adicionar vertices a lista de adjacencia
            add_adj(first, last);
            add_adj(last, first);

            result = true;
        }

        return result;
    }

    // Adicionar nova vertice
    void add_vertex() {

        this->vertices++;

        //Adicionar nova lista de adjacencia
        std::vector<uint32_t> it;
        this->adj.push_back(it);
    }

    // Funcoes para contar numero de componentes
    int num_components() {

        int num = 0; // variavel de resultado

        // Variavel para marcar vertices visitadas
        bool* visited = new bool[this->vertices];
        std::memset(visited, false,this->vertices*sizeof(bool)); // iniciando array com valor 'false'
    
        //Visitar todas as vertices
        for (int v = 0; v < this->vertices; v++) {
            if (visited[v] == false) {

                // Fazer um 'depth first search', retornando vertices atravessados
                auto vertexes = dfs(v, visited);

                // Ordenar vertices e imprimir na tela
                std::sort(vertexes.begin(), vertexes.end());
                for(int j = 0; j < vertexes.size(); j++) 
                    std::cout << vertexes.at(j) << ",";
                
                // aumentar numero de componentes
                num++;
                std::cout << "\n"; // dar espacamento
            }
        }

        // deletar array da memoria
        delete visited;

        return num;
    }

    // Funcao de 'depth first search'
    std::vector<char> dfs(int v, bool* visited) {

        // Marcar vertice como visitado
        visited[v] = true;

        // Criar array de char, iniciando com a vertice
        // que esta sendo visitada
        std::vector<char> resp = { intToChar(v) };

        // Pegar vizinhos de 'v'
        auto curr_vertex_adj = this->adj.at(v); 

        // Atravesar os vizinhos de 'v'
        for (int i = 0 ; i < curr_vertex_adj.size(); i++)

            // Se o vizinho de 'v' nao tiver sido visitado
            // visita-lo
            if (!visited[curr_vertex_adj.at(i)]) {

                // Pegar vizinhos visitados e armazena-los no resultaod
                auto tmp = dfs(curr_vertex_adj.at(i), visited);
                for(int j = 0; j < tmp.size(); j++) {
                    char aux = tmp.at(j);
                    resp.push_back(aux);
                }
            }

        return resp;
    }

    // Converter inteiro para caracetere
    char intToChar(int i) {
        return (char)(i + 97); // 97 = 'a' 
    }
};      

// Funcao utilitaria para conversao de 'char' para 'inteiro'
int charToInt(char c);

int main() {

    // Numero de casos testes
    int n;

    std::cin >> n;

    for(int i = 0 ; i < n; i++) {

        // Numero de vertices e arestas
        int v,e;

        // Criando grafo
        std::cin >> v >> e;
        Graph* g = new Graph(v);

        char v1,v2;
        for(int j = 0 ; j < e; j++) {

            // Fazer leitura da aresta 'j' do grafo
            std::cin >> v1 >> v2;

            // Adicionar vertice ao grafo
            // convertendo o char para um numero inteiro
            g->add_edge(v1 - 'a', v2 - 'a');
            
        }

        // Imprimindo o caso atual
        std::cout << "Case #" << i + 1 << ":" << std::endl;
        int num = g->num_components();
        std::cout << num << " connected components\n" << std::endl;

        // Deletar grafo da memoria
        delete g;

    }
}