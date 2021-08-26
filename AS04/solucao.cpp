/*
    Professor: Wladmir Cardoso Brandão
    Matéria: Laboratório de Projeto de Algoritmos
    Aluno: Lucas Santiago de Oliveira
    Matrícula: 650888
    Complexidade do algoritmo: O(n log n + n) -> n sendo o tamanho da maior string de entrada
    (n log n) -> Complexidade do sort
    (n)       -> Complexidade do deslocamento dentro do kruskal
    Complexidade de espaço: O(2n) -> n sendo o tamanho da entrada
    2n                            -> É criado um vetor paralelo no código algumas vezes
*/

#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iterator>

// Class containing the connected router and its price
class Routers {
public:
    uint32_t router, another_router, price;

    // Empty Constructor
    Routers() {
        this->router = 0;
        this->another_router = 0;
        this->price = 0;
    }

    // Default Constructor
    Routers(uint32_t router, uint32_t another_router, uint32_t price) {
        this->router = router;
        this->another_router = another_router;
        this->price = price;
    }
};

// Adding in the adjacency list the new 2 edges
void addEdgeAdjacencyList(std::vector<Routers> &routers, uint32_t router1, uint32_t router2, uint32_t price) {
    // Adding the first element on the adjacency list
    routers.push_back(*new Routers(router1, router2, price));
}

// To represent Disjoint Sets
struct DisjointSets {
    uint32_t *parent, *rnk;
    uint32_t n; // Number os edges
  
    // Constructor.
    DisjointSets(uint32_t n) {
        // Allocate memory
        this->n = n;
        parent = new uint32_t[n+1];
        rnk = new uint32_t[n+1];
  
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (uint32_t i = 0; i <= n; i++) {
            rnk[i] = 0;
  
            //every element is parent of itself
            parent[i] = i;
        }
    }
  
    // Find the parent of a node 'u'
    // Path Compression
    uint32_t find(uint32_t u) {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    // Union by rank
    void merge(uint32_t x, uint32_t y) {
        x = find(x), y = find(y);
  
        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
  
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

// Definition for sorting
bool sortByPrice(Routers pair1, Routers pair2) {
    return pair1.price < pair2.price;
}

// Getting the weight of the MST
uint32_t kruskalMST(std::vector<Routers> &routers) {
    uint32_t mst_wt = 0; // Initialize result
  
    // Sorting all edges
    std::sort(routers.begin(), routers.end(), sortByPrice);

    // Create disjoint sets
    DisjointSets ds(routers.size());
  
    // Iterate through all edges
    for (auto it = routers.begin(); it != routers.end(); it++) {
        int u = it->router;
        int v = it->another_router;
  
        int set_u = ds.find(u);
        int set_v = ds.find(v);
  
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v) {  
            // Update MST weight
            mst_wt += it->price;
  
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
  
    return mst_wt;
}

// Print in stdout what is inside the struct
void printRouters(std::vector<Routers> &routers) {
    for(auto it = routers.begin(); it < routers.end(); it++) 
        std::cout << "Edge: " << it->router << " connected to edge: " << it->another_router << " with the price: $" << it->price << std::endl;
}

int main() {
    uint32_t numrouters, cabos;
    std::cin >> numrouters >> cabos;
    std::cin.ignore();

    // Creating a adjacency list
    std::vector<Routers> routers;

    uint32_t router1, router2, price;
    while (!std::cin.eof()) {
        std::cin >> router1 >> router2 >> price;
        std::cin.ignore();

        addEdgeAdjacencyList(routers, router1, router2, price);
    }

    std::cout << kruskalMST(routers) << std::endl;

    return 0;
}