#include "NBody.h"

NBody::NBody(const std::string& filename)
{
    std::ifstream NBodyFile(filename);
    double value = 0;

    while(NBodyFile >> value){
        bodies.push_back(Particle());
        bodies.back().Rx = value;
        NBodyFile >> value; bodies.back().Ry = value;
        NBodyFile >> value; bodies.back().Vx = value;
        NBodyFile >> value; bodies.back().Vy = value;
        NBodyFile >> value; bodies.back().mass = value;
    }
    NBodyFile.close();
    int i = 0;
    while(i++ < bodies.size()){
        forceX.push_back(0);
        forceY.push_back(0);
    }
}

void NBodyThreadUpdate(const std::vector<Particle>::iterator& currentBody, std::vector<Particle>::iterator nBodyIterator,
                       const std::vector<Particle>::iterator& nBodyEnd, double* forceX, double* forceY)
{
    *forceX = 0;
    *forceY = 0;
    double gForce = 0;
    while(nBodyIterator != nBodyEnd){
        if(nBodyIterator != currentBody){
            gForce = currentBody->gravForce(*nBodyIterator);
            *forceX += currentBody->forceComponentX(*nBodyIterator, gForce);
            *forceY += currentBody->forceComponentY(*nBodyIterator, gForce);
        }
        nBodyIterator++;
    }
}

void NBody::updateNbodies()
{
    std::cout << bodies.size() << std::endl;
    double gForce = 0;
    double accelX, accelY;
    accelX = accelY = 0;
    std::vector<Particle>::iterator bodyIterator = bodies.begin();
    std::vector<Particle>::iterator currentBody = bodies.begin();
    std::vector<std::thread> nBodyThreads(bodies.size());
    int i = 0;
    while(currentBody != bodies.end()){
        bodyIterator = bodies.begin();
        forceX[i] = 0;
        forceY[i] = 0;
        nBodyThreads[i] = std::thread(NBodyThreadUpdate, currentBody, bodies.begin(), bodies.end(), &forceX[i], &forceY[i]);
//        while(bodyIterator != bodies.end()){
//            if(bodyIterator != currentBody){
//                gForce = currentBody->gravForce(*bodyIterator);
//                forceX[i] += currentBody->forceComponentX(*bodyIterator, gForce);
//                forceY[i] += currentBody->forceComponentY(*bodyIterator, gForce);
//            }
//            bodyIterator++;
//        }
//        currentBody++; i++;
        currentBody++; i++;
    }
    i = 0;
    while(i < bodies.size()){
        nBodyThreads[i++].join();
    }
    bodyIterator = bodies.begin(); i = 0;
    while(bodyIterator != bodies.end()){
        std::cout << bodyIterator->Rx << "\t" << bodyIterator->Ry << std::endl;
        accelX = bodyIterator->accelComponentX(forceX[i]);
        accelY = bodyIterator->accelComponentY(forceY[i]);
        bodyIterator->updateVx(accelX);
        bodyIterator->updateVy(accelY);
        bodyIterator->updateRx();
        bodyIterator->updateRy();
        std::cout << bodyIterator->Rx << "\t" << bodyIterator->Ry << std::endl;
        std::cout << "=====================" << std::endl;
        bodyIterator++;i++;
    }

}

NBody::~NBody()
{
    //dtor
}
