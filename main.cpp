#include <iostream>
#include <vector>
#include "particle.h"

int main()
{
    size_t totalBodies = 2;
    std::vector<Particle> bodies(totalBodies);
    std::vector<double> forceX(totalBodies, 0);
    std::vector<double> forceY(totalBodies, 0);
    std::vector<Particle>::iterator bodiesIterator = bodies.begin();
    std::vector<Particle>::iterator currentBody = bodies.begin();
    bodies[0].Rx = -10; bodies[0].Ry = -10; bodies[0].mass = 10000;
//    bodies[0].Vx = 10; bodies[0].Vy = -3;
    bodies[1].Rx = 10; bodies[1].Ry =  10; bodies[1].mass = 10000;
    bodies[2].mass = 49;
    int i = 0;
    double gForce = 0;
    double accelX, accelY;
    while(bodiesIterator != bodies.end()){
        forceX[i] = forceY[i] = 0;
        currentBody = bodies.begin();
        while(currentBody != bodies.end()){
            if(currentBody != bodiesIterator){
                gForce = bodiesIterator->gravForce(*currentBody);
                forceX[i] += bodiesIterator->forceComponentX(*currentBody, gForce);
                forceY[i] += bodiesIterator->forceComponentY(*currentBody, gForce);
            }
            currentBody++;
        }
        bodiesIterator++; i++;
    }

    bodiesIterator = bodies.begin(); i = 0;

    while(bodiesIterator != bodies.end()){
        std::cout << bodiesIterator->Rx << "\t" << bodiesIterator->Ry << std::endl;
        accelX = bodiesIterator->accelComponentX(forceX[i]);
        accelY = bodiesIterator->accelComponentY(forceY[i]);
        bodiesIterator->updateVx(accelX);
        bodiesIterator->updateVy(accelY);
        bodiesIterator->updateRx();
        bodiesIterator->updateRy();
        std::cout << bodiesIterator->Rx << "\t" << bodiesIterator->Ry << std::endl;
        std::cout << "-----------------" << std::endl;
        bodiesIterator++; i++;
    }



    return 0;
}
