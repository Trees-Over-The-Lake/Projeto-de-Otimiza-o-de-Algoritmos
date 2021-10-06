// NÃO USAR -- 0% FUNCIONAL

#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
public:
    // Classe de Edge para o grafo
    class Edge {
        public:
        std::pair<std::string, std::string> conexao;
        int peso;
    };

    std::vector<std::string> *todasEstacoes;
    std::vector<Edge> Edges;

    // Inserir nova aresta no grafo
    void inserir(std::string verticeA, std::string verticeB, int peso);
    // Escrever grafo na tela
    void print();
};

// Inserir nova aresta no grafo
void Graph::inserir(std::string verticeA, std::string verticeB, int peso) {
    Edge *edge = new Edge();
    std::pair<std::string, std::string> conexao;
    conexao.first = verticeA;
    conexao.second = verticeB;
    edge->conexao = conexao;
    edge->peso = peso;

    this->Edges.push_back(*edge);
}

// Estrutura para salvar os subsets do union-find
struct subset {
    int parent;
    int rank;
};
 

// Path compression
int find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// Unir X e Y
void Union(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Comparar o peso de dois grafos
int edgeComp(Graph::Edge a1, Graph::Edge a2) {
    return a1.peso > a2.peso;
}
 
// Kruskal
int Kruskal(Graph *graph) {
    int V = graph->todasEstacoes->size();
    Graph::Edge result[V]; // Salvar o resultado da MST
    int e = 0; // Index variable, usado no result[]
    int i = 0; // Index variable, usado no edges ordenado
 
    // Ordenando grafo
    std::sort(graph->Edges.begin(), graph->Edges.end(), edgeComp);

    subset* subsets = (subset*) malloc(V * sizeof(subset));
 
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    while (e < V - 1 && i < graph->Edges.size()) {
        auto next_edge = graph->Edges.at(i++);

        auto posX = std::find(graph->Edges.begin(), graph->Edges.end(), next_edge.conexao.first);
        auto posY = std::find(graph->Edges.begin(), graph->Edges.end(), next_edge.conexao.second);
        int x = find(subsets, *posX);
        int y = find(subsets, *posY);
 
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        minimumCost += result[i].peso;
    }
 
    return minimumCost;
}

// Escrever grafo na tela
void Graph::print() {
    std::cout << "Estações: " << std::endl;

    for(auto i = this->todasEstacoes->begin(); i != this->todasEstacoes->end(); i++) {
        std::cout << *i << std::endl;
    }

    std::cout << "Ligações: A -> B | peso" << std::endl;

    for(auto i = this->Edges.begin(); i != this->Edges.end(); i++) {
        std::cout << i->conexao.first << " -> " << i->conexao.second << " | " << i->peso << std::endl; 
    }
}

int main() {
    int numEstacoes, numConeccoes;
    std::cin >> numEstacoes >> numConeccoes;
    std::cin.ignore();

    Graph *grafo;
    while(numEstacoes != 0) {

        grafo = new Graph();
        std::vector<std::string> estacoes;

        for (int i = 0; i < numEstacoes; i++) {
            std::string nomeEstacao;
            std::cin >> nomeEstacao;
            std::cin.ignore();
            estacoes.push_back(nomeEstacao);
            grafo->todasEstacoes = &estacoes;
        }

        for (int i = 0; i < numConeccoes; i++) {
            std::string verticeA;
            std::string verticeB;
            int peso;

            std::cin >> verticeA >> verticeB >> peso;
            std::cin.ignore();
            grafo->inserir(verticeA, verticeB, peso);
        }

        std::string comecarKruskal;
        std::cin >> comecarKruskal;
        std::cin.ignore();

        int result = Kruskal(grafo);
        if(result < 0)
            std::cout << "Impossible" << std::endl;
        
        else
            std::cout << result << std::endl;

        delete grafo;
        std::cin >> numEstacoes >> numConeccoes;
        std::cin.ignore();
    }


    return 0;
}