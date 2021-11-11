

#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <climits>

struct Vertice {
    // Todas as ligações das cidades B e seus devidos tempos
    std::vector<std::pair<int, int>> ligacoes;
};

class Grafo {
private:
    Vertice *vertices; // O tamanho do vetor de vertices é as cidades A

public:
    Grafo(int numCidades) {
        this->vertices = new Vertice[numCidades];
    }

    // Inserir vertice no grafo
    void inserirVertice(int cidadeA, int cidadeB, int tempo);
    // Descobrir a menor distancia entre duas cidades
    int minDistancia(int cidadeA, int cidadeB); 

    // Get tempo entre dois pontos O(n)
    int getDistancia2Pontos(int cidadeA, int cidadeB) {
        for(auto i = this->vertices[cidadeA].ligacoes.begin(); i != this->vertices[cidadeA].ligacoes.end(); i++) {
            if(i->first == cidadeB)
                return i->second;
        }

        return -1;
    }

    // get vertices
    Vertice* getVertices() {
        return this->vertices;
    }
};

// Inserir novo elemento no grafo
void Grafo::inserirVertice(int cidadeA, int cidadeB, int tempo) {
    std::pair<int, int> cidadeBETempo;
    cidadeBETempo.first = cidadeB;
    cidadeBETempo.second = tempo;

    this->vertices[cidadeA].ligacoes.push_back(cidadeBETempo);
}

// Algoritmo para encontrar o menor caminho
int minDist(int cidadeAtual, int cidadeFinal, Grafo *caminho, int distanciaSomada) {
    if(cidadeAtual == cidadeFinal)
        return distanciaSomada;

    else
        for(auto i = caminho->getVertices()->ligacoes.begin(); i != caminho->getVertices()->ligacoes.end(); i++) 
            return minDist(i->first, cidadeFinal, caminho, caminho->getDistancia2Pontos(cidadeAtual, i->first) + distanciaSomada);
    
}

// Descobrir a menor distancia entre duas cidades
// -1 -> não tem caminho da cidade A para a B
int Grafo::minDistancia(int cidadeA, int cidadeB) {
    int menorDistancia = -1;

    menorDistancia = minDist(cidadeA, cidadeB, this, 0);

    return menorDistancia;
}


int main() {
    int numCidades, acordoMensagens;
    std::cin >> numCidades >> acordoMensagens;
    
    // Grafo que será usado durante a resolução do problema
    Grafo *g;

    while(numCidades != 0) {
        // Enviar as cartas da cidade A para a B em X horas
        int cidadeA, cidadeB, horas;
    
        // Criar um grafo do tamanho do numero de cidades
        g = new Grafo(numCidades);

        // Descobrir os acordos de mensagens e quanto tempo leva
        for(int i = 0; i < acordoMensagens; i++) {
            // Adicionando no grafo
            std::cin >> cidadeA >> cidadeB >> horas;
            g->inserirVertice(cidadeA-1, cidadeB-1, horas);
        }


        // Consultas
        int numConsultas, resultadoConsulta; // Valores relativos a consulta
        int cidadeInicial, cidadeFinal;      // Pesquisa entre o ponto A para o B
        std::cin >> numConsultas;
        for(int i = 0; i < numConsultas; i++) {
            // Recebendo as consultas e testando-as
            std::cin >> cidadeInicial >> cidadeFinal;
            resultadoConsulta = g->minDistancia(cidadeInicial-1, cidadeFinal-1);

            // Escrevendo os resultados na tela
            if(resultadoConsulta == -1) 
                std::cout << "Nao e possivel entregar a carta" << std::endl << std::endl;
            
            else
                std::cout << resultadoConsulta << std::endl;
        
        }

        delete g;
        std::cin >> numCidades >> acordoMensagens;
    }

    return 0;
}