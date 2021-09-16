#include <iostream>
#include <sys/unistd.h>

int thread_entry(int foo, int bar) {
    return foo + bar;
}



int main() {

    int id = fork();

    if(id == 0) 
        for(int i = 0; i < 3; i++)
            id = fork();

    if(id != 0) std::cout << thread_entry(5, 7) << std::endl;
    if(id == 0) std::cout << thread_entry(4, 9) << std::endl;

    std::string abc;
    std::cin >> abc;
    
    return 0;
}