#ifndef LATTICE_H
#define LATTICE_H

#include "site.h"

class Lattice {

  public:
    double isingStrength = -1.0;    //write a function to change this soon....
    int dim;
    int latticeSize;
    Site *lat;
    int volume;

    Lattice(int);      //Default constructor

    double  configurationEnergy(int, int);
    double  totalMagnetization(void);
    void    warmupSweep(int, double);
    void    randomMcIteration(double);
    void    linearMcIteration(double);
    double  twoDConfigurationEnergy(int);


        //Helpers
    int *getNeighbors(int, int, int);
    inline int mapToArray(int, int, int);
};

#endif /* LATTICE_h */
