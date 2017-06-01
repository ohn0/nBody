#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "particle.h"
#include "NBody.h"
#include <ctime>
int main()
{
    NBody Nsystem("nBodies.txt");
    int i = 0;
    std::clock_t start = std::clock();
    while(i++ < 10000){
        Nsystem.updateNbodies();
    }
    Nsystem.printNbodies();
    std::cout << ((std::clock() - start) / ((double) CLOCKS_PER_SEC)) << std::endl;
    return 0;
}
