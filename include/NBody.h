#ifndef NBODY_H
#define NBODY_H
#include "particle.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
class NBody
{
    std::vector<Particle> bodies;
    std::vector<double> forceX;
    std::vector<double> forceY;
    std::vector<std::thread> bodyThreads;
    public:
        NBody(const std::string&);
        virtual ~NBody();
        void updateNbodies();
        void printNbodies();

};

#endif // NBODY_H
