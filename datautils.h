#ifndef DATAUTILS_H
#define DATAUTILS_H

#include "lattice.h"

double systemEnergy(const Lattice, int);
double systemMagnetization(const Lattice);
void collectMcData(Lattice, int, double);

#endif
