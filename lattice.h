#ifndef LATTICE_H
#define LATTICE_H

#include "site.h"

class Lattice {

  public:
    double isingStrength = 1.0;    //write a function to change this soon....
    int dim;
    int xLen, yLen, zLen;
    Site *lat;

    Lattice(int, int, int);      //Default constructor

    double  configurationEnergy(int);
    void    sweep(void);

        //Helpers
    int *getNeighbors(int, int, int);
    inline int map(int, int, int);
};


#endif /* LATTICE_h */