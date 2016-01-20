/* Patrick Ryan
 * Last edited: 13/01/16
 *
 * Source file for the lattice class and associated methods.
 *
 * Lattice object parameters:
 * dim:             int     Spatial dimension of the lattice
 * xLen:            int     length of the lattice in the x direction
 * yLen:            int     length of the lattice in the y direction
 * zLen:            int     length of the lattice in the z direction
 * periodicBound:   bool    0 = open boundary system, 1 = periodic boundary
 * name:            char[]  Name tag of the lattice.
 *
 * Lattice methods:
 *
 * Lattice()
 *      Default constructor
 * Lattice(dim, xLen, yLen, zLen, periodicBound, name)
 *      Full constructor
 * ......
 */

#include <iostream>
#include <exception>

#include "lattice.h"
#include "site.h"
#include "MersenneTwister.h"

using namespace std;

MTRand prng;

Lattice::Lattice(int x, int y, int z){
    xLen = x;
    yLen = y;
    zLen = z;
    lat = (Site *)malloc(sizeof(Site) * xLen * yLen * zLen);
    int sum = 0; //debug
    for (int i = 0; i < xLen; ++i){
      for (int j = 0; j < yLen; ++j){
        for (int k = 0; k < zLen; ++k){
          // Get a random spin, init site and insert it into the mapped lattice.
          int m = map(i, j, k);
          double num = prng.randDblExc();
          int spin = (num < 0.5) ? -1 : 1;

          int *neighbors = getNeighbors(i, j, k);
          Site s(neighbors, spin);
          lat[m] = s;
          sum += lat[m].spin;
        }
      }
    }
    cout << "SUM: " << sum  << " percent off even: " << 100.0 * sum / (xLen * yLen *zLen) << endl;
}

int* Lattice::getNeighbors(int i, int j, int k){
  int *n = (int *)malloc(sizeof(int) * NUMNEIGHBOR);
  // x axis neighbors
  n[0] = map(i - 1, j, k);
  n[1] = map(i + 1, j, k);
  // y axis neighbors
  n[2] = map(i, j - 1, k);
  n[3] = map(i, j + 1, k);
  // z axis neighbors
  n[4] = map(i, j, k - 1);
  n[5] = map(i, j, k + 1);
  return n;
}

inline int Lattice::map(int i, int j, int k){
  return i * j * k + j * k + k;
}

double Lattice::configurationEnergy(int m){
    double energy = 0;
    int s = lat[m].spin;

    for (int i : lat[m].nnIndex){
        Site testSite = lat[i];
        int testSpin = testSite.spin;
        energy += s * testSpin;
    }
    return isingStrength * energy;
}

void Lattice::sweep(void){
  // randomly pick xLen * yLen *zLen sites and determine wheather to flip them
  // based on their boltzmann factor.
}
