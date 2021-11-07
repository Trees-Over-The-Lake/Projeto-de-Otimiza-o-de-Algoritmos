/*
    Solução para o urijudge 1513 -> https://www.beecrowd.com.br/judge/pt/problems/view/1513
    Professor: Wladmir Cardoso Brandão
    Matéria: Laboratório de Projeto de Algoritmos
    Aluno: Lucas Santiago de Oliveira
    Matrícula: 650888
    Complexidade do algoritmo: O(n * m) -> Sendo n e m os tamanhos 
*/

#include <unistd.h>
#include <limits>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

// Pegando o valor de infinito dentro de <limits>
#define INF std::numeric_limits<int>::max()

// Peças que serão usadas
#define PEAO     'P'
#define CAVALO   'C'
#define BLOQUEIO '#'

// Definindo estruturas padroes que sao usadas pelo programa
typedef std::pair<int,int> coordenadas;
typedef std::vector<std::vector<int>> matrix;

// Definindo variaveis que guardam os principais movimentos do cavalo, sempre
// em formato de 'L'
int const dx[] = {2, 2,-2,-2,1, 1,-1,-1};
int const dy[] = {1,-1, 1,-1,2,-2, 2,-2};

// Classe do tabuleiro de xadrez
class Xadrez {
private:
  // Dimensoes do tabuleiro
  int n;
  int m;

  // Posições possíveis do cavalo
  coordenadas posicoesCavalo;

  // BFS no caminho dos peos
  matrix caminhoDosPeos;
  matrix memo;

  std::map<coordenadas, int> indecesPeos; // Posicao dos peos
  std::vector<std::string> grid;  // Grid do tabuleiro

public:
  //Construtor, definindo as dimensoes do tabuleiro
  Xadrez(int n, int m) { this->n = n; this->m = m; this->grid.resize(n); }

  // Fazendo a leitura do tabuleiro 
  void lerEntrada() {
    // Variavel para ajudar a organizar os indices dos peos
    int indx = 0;

    for(int i = 0, cnt = 0; i < n ; ++i){
      // Ler uma linha do tabuleiro
      std::cin >> grid[i];

      for(int j = 0; j < m; ++j) {
        // Marcando a posicao do cavalo
        if(this->grid[i][j] == CAVALO) this->posicoesCavalo = coordenadas({i,j});

        // Marcando a posicao do peao, e colocando seu indice
        if(this->grid[i][j] == PEAO) indecesPeos[{i,j}] = indx++;
      }
    }
  }

  // Breadth first search: encontrar melhor caminho
  void bfs(int peaoX, int peaoY){
    // Iniciando matrix de distancias e iniciando todos valores como -1
    matrix distancia(n, std::vector<int>(m, -1));
    std::queue<coordenadas> filaPeao; // Queue de pesquisa

    // Adicionar primeiro peao(no) a se pesquisar
    filaPeao.push({peaoX, peaoY});
    distancia[peaoX][peaoY] = 0;

    while(!filaPeao.empty()){
      //Pegar o primeiro peao
      coordenadas x = filaPeao.front();
      filaPeao.pop();

      // Visitar a vizinha do cavalo(lembrando que o
      // cavalo anda em "L")
      for(int i = 0; i < 8 ; ++i){
        int novoPontoX = x.first + dx[i];
        int novoPontoY = x.second + dy[i];

        // Verificando se esta eh uma posicao valida, e se nada foi preenchido
        // na matrix de distancias
        if(ehValido(novoPontoX,novoPontoY) || distancia[novoPontoX][novoPontoY] != -1) 
          continue;

        // Adiciona valor valido
        distancia[novoPontoX][novoPontoY] = distancia[x.first][x.second] + 1;
        filaPeao.push({novoPontoX, novoPontoY}); // Adicionar proximo peao para pesquisa
      }
    }

    // indice do peao que foi usado para atravessar grafo
    int indexP = indecesPeos[{peaoX,peaoY}];
    for(auto it : indecesPeos){
      int current_peao_index = it.second, x = it.first.first, y = it.first.second;

      // Registrar distancia entre os peos current_peao_index e indexP
      caminhoDosPeos[indexP][current_peao_index] = caminhoDosPeos[current_peao_index][indexP] = distancia[x][y];
    }
  }

  // Verificar se as coordenadas providas sao validos dentro do tabuleiro e
  // nao existe bloqueio
  inline bool ehValido(int x,int y) { return x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == BLOQUEIO; }

  // Funcao inicial para o problema
  int encontrarMenorCaminho() {
    // Armazenar o numero de peoes
    int num_peaos = indecesPeos.size();

    // Iniciar processo de fazer o grafo do caminho dos peoes
    indecesPeos[posicoesCavalo] = num_peaos;
    caminhoDosPeos.assign(num_peaos+1, std::vector<int>(num_peaos+1, 0));
    
    // Calcular o caminho para todos os peos do tabuleiro
    for(auto x : indecesPeos)
        bfs(x.first.first, x.first.second);

    // Iniciar memo
    int arr_depth = 1<<num_peaos;
    memo = matrix(num_peaos+1,std::vector<int>(arr_depth,-1));
    
    return movimentCalculation(num_peaos, arr_depth-1);
  }

  int movimentCalculation(int peao, int mascara){
    if(mascara == 0) return caminhoDosPeos[peao][indecesPeos.size() - 1];    
    int& time = memo[peao][mascara]; // Pegar valor no memo

    // Memoization
    if(time != -1) return time;

    // Colocar tempo como infinito para nao resultar 
    time = INF;

    // Navegar por todos os peoes, exceto o atual
    for(int i = 0; i < indecesPeos.size() - 1 ; ++i){
      if(i == peao || !(mascara & (1<<i))) continue;

      time = std::min(time, caminhoDosPeos[peao][i] + movimentCalculation(i, mascara-(1<<i)));
    }

    return time;
  }
};

int main(){
  // Entradas
  int n, m, k;
  while(std::cin >> n >> m >> k){
    if(n == 0 && m == 0 && k == 0) goto TERMINAR_CODIGO;

    Xadrez cb(n,m); 
    cb.lerEntrada();

    // Resolver problema
    std::cout << cb.encontrarMenorCaminho() << std::endl;
  }

TERMINAR_CODIGO:
  return 0;
}