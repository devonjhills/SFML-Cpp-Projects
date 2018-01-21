#include <iostream>
#include <stdexcept>
#include "nbody.hpp"

using namespace DancePlanetsDance; //NOLINT

//sample usage: ./NBody 157788000.0 25000.0 < planets.txt 

int main(int argc, char* argv[]) {
    if (argc != 3) {
        throw std::runtime_error("Format: ./NBody [simulation_time] "
                                 "[delta_time] < file.txt");
    }

    double simulationTime = atof(argv[1]);
    double deltaT = atof(argv[2]);

    double winSize = 500.0;
    int numBodies;
    double radius;

    std::cin >> numBodies >> radius;

    Universe newUni(numBodies, radius, winSize, simulationTime, deltaT);
    newUni.run_universe();

    return 0;
}
