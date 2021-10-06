/*
    Lucas Santiago de Oliveira - 650888
    Complexidade: O(e log v) -> e sendo o número de edges e v sendo o número de vertex
*/

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <map>
#include <queue>

// Classe de grafos
class Graph {
    private: 
    // Estrutura para armazenar as Edges
    struct Edge {
        std::string i, j;
        int w;

        Edge(std::string I, std::string J, int W): i(I), j(J), w(W) {
            this->i = I;
            this->j = J;
            this->w = W;
        }

        bool operator < (const Edge& e ) const {
            return w > e.w;
        }
    };

    // Estrutura para os DisjoinSets
    struct DisjoinSets {
        private: 
            std::vector<std::pair<int,int>> nodes; // Vetor de parentesco

        public:
            DisjoinSets(int n) {
                for(int i = 0; i < n ; i++) 
                    this->nodes.push_back({0,i});
            }

            // Achar o pai do nó index
            int find(int index) {
                if(index != this->nodes.at(index).second)
                    this->nodes.at(index).second = find(this->nodes.at(index).second);
                return this->nodes.at(index).second;
            }

            //Fazer uma combinacao do no 'x' com o no 'y'
            void merge(int x,int y) {
                x = find(x);
                y = find(y);

                if(this->nodes.at(x).first > this->nodes.at(y).first)
                    this->nodes.at(y).second = x;
                else 
                    this->nodes.at(x).second = y;

                if(this->nodes.at(x).first == this->nodes.at(y).first)
                    this->nodes.at(y).first++;
                    
            }

    };
        int numVertices;
        int numEdges;

        // Armazenar arestas e seus respectivos pesos
        std::priority_queue<Edge> edges;
        std::map<std::string,int> vertexIds;

    public:
        Graph() { this->numVertices = 0; }
        int vertices_num() { return this->numVertices; }
        int edges_num() { return this->numEdges; }

        // Add vertex
        void add_vertex(std::string vertex_name) { this->vertexIds[vertex_name] = this->numVertices++; }

        // Adicionar aresta ao grafo 
        void add_edge(std::string first, std::string last, int value) {
            this->numEdges++;
            this->edges.push(Edge(first, last, value));
        }

        // Krustal MST
        int kruskal() {
            if(this->numVertices <= 1) { return 0; }
            int totalW = 0;

            // DisjointSet
            DisjoinSets ds(this->numVertices);
            while (!edges.empty()) {
                Edge it = edges.top();

                std::string src = it.i;
                std::string dst = it.j;
        
                int parent_src = ds.find(this->vertexIds[src]);
                int parent_dst = ds.find(this->vertexIds[dst]);

                // Não gerar ciclos
                if (parent_src != parent_dst) {
                    ds.merge(parent_src, parent_dst);
                    totalW += it.w;

                    if(--this->numVertices <= 1)
                        return totalW;
                }

                edges.pop();
            }

            return -1;
        }
};      

int main() {

    int numStations;
    int numConnections;

    std::cin >> numStations >> numConnections;
    std::cin.ignore();

    while(numStations != 0) {
        Graph grafo;
        std::string stationName;

        // Add Vertex
        for(int i = 0; i < numStations; i++) {
            std::cin >> stationName;
            std::cin.ignore();
            grafo.add_vertex(stationName);
        }

        // Leitura das arestas
        for(int i = 0; i < numConnections; i++) {
            std::string src, dst;
            int weight;

            std::cin >> src >> dst >> weight;

            grafo.add_edge(src,dst,weight);
        }

        std::string comecar;
        std::cin >> comecar;
        std::cin.ignore();

        int result = grafo.kruskal();
        
        if(result < 0) 
            std::cout << "Impossible" << std::endl;
        else 
            std::cout << result << std::endl;

        std::cin >> numStations >> numConnections;
        std::cin.ignore();
    }
    
    return 0;
}