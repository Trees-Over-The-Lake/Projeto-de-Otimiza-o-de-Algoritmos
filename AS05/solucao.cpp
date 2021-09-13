#include <iostream>
#include <cstdint>
#include <vector>

class Graph {
public:
    std::vector<wchar_t> *vertex; // List of all vertex connections

    // Printing the results from the graph
    void print_results(uint32_t caseNumber, uint32_t numberOfCases) {
        std::cout << "Case #" << caseNumber << ":" << std::endl;

        for(uint32_t i = 0; i < numberOfCases; i++) {
            for(wchar_t vertex : this->vertex[i]) {
                std::wcout << vertex << ", ";
            }
            if(this->vertex[i].size() != 0) std::cout << std::endl;
        }

        std::cout << numberOfCases << " connected components" << std::endl << std::endl;
    }
};

// Solution for uri judge 1082 -> https://www.urionlinejudge.com.br/judge/pt/problems/view/1082
int main() {
    // Setting the locale for the file -> using Unicode
    std::locale l("pt_BR.UTF-8");
    std::wcin.imbue(l);
    std::wcout.imbue(l);

    // All test that will have in the stdin
    uint32_t testCases;
    std::wcin >> testCases;
    std::wcin.ignore();

    uint32_t vertex, edge;
    Graph *graph;
    for(uint32_t i = 1; i != testCases; i++) {
        std::wcin >> vertex >> edge;
        std::cin.ignore();

        graph = new Graph();  // Creating the graph in memory
        graph->vertex = new std::vector<wchar_t>[vertex];  // Setting the number of vertex for the graph
        std::pair<wchar_t, wchar_t> edgeConnection;    
        for(uint32_t j = 0; j < edge; j++) {
            // Pair to hold a connection between 2 edges
            std::wcin >> edgeConnection.first >> edgeConnection.second;
            std::wcin.ignore();

            graph->vertex[edgeConnection.first - L'a'].push_back(edgeConnection.second);
        }

        graph->print_results(i, vertex);
        delete graph;
    }

    return 0;
}