#include <cstdint>
#include <string>
#include <iostream>

// Solucao para o problema de subsequencias
int main(int argc, char **argv) {
    uint16_t casosTeste;
    std::cin >> casosTeste;
    std::cin.ignore();

    std::string casos[casosTeste];
    for(uint16_t i = 0; i < casosTeste; i++) 
        std::cin >> casos[i];
    

    uint16_t numSubsequencias;
    std::cin >> numSubsequencias;
    std::cin.ignore();

    std::string subsequencias[numSubsequencias];
    for(uint16_t i = 0; i < numSubsequencias; i++) 
        std::cin >> subsequencias[i];
    
    
    return 0;
}