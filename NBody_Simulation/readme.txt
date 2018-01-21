Make commands:

make (or make all)
 - makes both NBody and NTest executables
make main
 - makes NBody executable
make test
 - makes NTest executable

/*****************************************************************************/

NBody Simulation Overview:

This program runs using a file provided in the command line. The file provides
SpaceObject bodies (in this case, planets) to simulate gravity and orbits in
space. The simulation is based on Newtonian mathematics, including the laws of
universal gravitation, the principle of superposition, Newton's second law
of motion, and the leapfrog finite difference approximation scheme. The main
function to run the program only needs to create a universe object and use
the run_universe member function.

/*****************************************************************************/

NBody Simulation Implementation:

The bulk of the code is within the universe class itself. The class is
responsible for holding all of the Stars, Planets, and any other type of
SpaceObject that could be implemented in the future. The universe then uses
the update_planets function to calculate the movement of each planet. It must
be within the universe class because the movement of each body is dependent
on each other body with gravity in the system.

The file provided give the carteisian coordinates (origin at the screen center)
of the bodies, which then must be converted into SFML coordinates (origin at
the top left corner of the screen). We also need to rescale the universe
radius to fit onto the simulation screen.

/*****************************************************************************/
