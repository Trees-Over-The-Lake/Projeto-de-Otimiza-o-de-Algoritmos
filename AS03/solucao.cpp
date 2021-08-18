#include <cstdint>
#include <string>
#include <iostream>

bool existeSubstring(std::string string, std::string substring) {
    uint16_t posEncontrado = 0;

    for(char c : string) {
        if(c == substring.at(posEncontrado))
            posEncontrado++;

        // Se deslocar corretamente toda a substring e chegar até o final
        // significa que toda ele foi encontrada na string original
        if(posEncontrado == substring.length())
            return true;
    }

    return false;
}

// Solucao para o problema de subsequencias
int main(int argc, char **argv) {
    uint16_t casosTeste;
    std::cin >> casosTeste;
    std::cin.ignore();

    std::string caso;
    for(uint16_t i = 0; i < casosTeste; i++) {
        std::cin >> caso; 

        uint16_t queries; 
        std::cin >> queries; 
        std::cin.ignore();

        std::string subsequencia;
        for(uint16_t j = 0; j < queries; j++) {
            std::cin >> subsequencia; 

            if(existeSubstring(caso, subsequencia))
                std::cout << "Yes" << std::endl;
            else
                std::cout << "No" << std::endl;
        }
    }
    return 0;
}