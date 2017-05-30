#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "particle.h"
#include "NBody.h"

int main()
{
    NBody Nsystem("nBodies.txt");
    Nsystem.updateNbodies();
    return 0;
}
