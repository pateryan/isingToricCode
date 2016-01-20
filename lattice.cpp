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
 * Lattice(xLen, yLen, zLen)
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
    volume = xLen * yLen * zLen;
    lat = (Site *)malloc(sizeof(Site) * volume);

    for (int k = 0; k < zLen; ++k){
      for (int j = 0; j < yLen; ++j){
        for (int i = 0; i < xLen; ++i){
          // Get a random spin, init site and insert it into the mapped lattice.
          int m = map(i, j, k);
          double num = prng.randDblExc();
          int spin = (num < 0.5) ? -1 : 1;

          int *neighbors = getNeighbors(i, j, k);
          Site s(neighbors, spin);
          lat[m] = s;
        }
      }
    }


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
  if (i < 0){
      i = xLen - 1;
  }
  if (j < 0){
      j = yLen - 1;
  }
  if (k < 0){
      k = zLen - 1;
  }
  if (i > xLen - 1){
      i = 0;
  }
  if (j > yLen - 1){
      j = 0;
  }
  if (k > zLen - 1){
      k = 0;
  }
  return xLen * yLen * k + xLen * j + i;
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

void Lattice::monteCarloSweep(int iterations, double temperature){
  int randIndex;
  double randNum;
  double transitionProbability, initEnergy, flipEnergy, energyDiff;

  // randomly pick iterations number of sites sites and determine wheather to flip them
  // based on their boltzmann factor.
  for (int i = 0; i <= iterations; ++i){
    randIndex = (int)prng.randInt(volume);
    initEnergy = configurationEnergy(randIndex);
    //Flip site and take energy difference
    lat[randIndex].spin *= -1;
    flipEnergy = configurationEnergy(randIndex);

    energyDiff = initEnergy - flipEnergy;

    if (energyDiff < 0){
      continue;
    } else {
      randNum = prng.randDblExc();
      transitionProbability = exp(-energyDiff / temperature);

      if (randNum < transitionProbability){
        continue;
      } else {
        lat[randIndex].spin *= -1;
      }
    }
  }
}
