#ifndef NBODY_H
#define NBODY_H
#include "particle.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
class NBody
{
    std::vector<Particle> bodies;
    std::vector<double> forceX;
    std::vector<double> forceY;
    public:
        NBody(const std::string&);
        virtual ~NBody();
        void updateNbodies();

};

#endif // NBODY_H
