/* Patrick Ryan
 * Last edited: 13/01/16
 *
 * Source file for the lattice class and associated methods.
 *
 * Lattice object parameters:
 * latticeSize      int     side lenght of the lattice.
 * periodicBound:   bool    0 = open boundary system, 1 = periodic boundary
 * name:            char[]  Name tag of the lattice.
 */

#include <iostream>
#include <cmath>

#include "lattice.h"
#include "site.h"
#include "MersenneTwister.h"
#include "datautils.h"

using namespace std;

MTRand prng;

Lattice::Lattice(int sideLen){
    latticeSize = sideLen;
    volume = latticeSize * latticeSize * latticeSize;
    lat = (Site *)malloc(sizeof(Site) * volume);

    for (int k = 0; k < latticeSize; ++k){
      for (int j = 0; j < latticeSize; ++j){
        for (int i = 0; i < latticeSize; ++i){
          // Get a random spin, init site and insert it into the mapped lattice.
          int m = mapToArray(i, j, k);
          double num = prng.randDblExc();
          int spin = (num < 0.5) ? -1 : 1;

          int *neighbors = getNeighbors(i, j, k);
          Site s(neighbors, spin);
          lat[m] = s;
        }
      }
    }
}

int* Lattice::getNeighbors(int x, int y, int z){
  int *n = (int *)malloc(sizeof(int) * NUMNEIGHBOR);
  // x axis neighbors
  n[0] = mapToArray(x - 1, y, z);
  n[1] = mapToArray(x + 1, y, z);
  // y axis neighbors
  n[2] = mapToArray(x, y - 1, z);
  n[3] = mapToArray(x, y + 1, z);
  // z axis neighbors
  n[4] = mapToArray(x, y, z - 1);
  n[5] = mapToArray(x, y, z + 1);

  return n;
}

int Lattice::mapToArray(int i, int j, int k){
  if (i < 0){
      i = latticeSize - 1;
  }
  if (j < 0){
      j = latticeSize - 1;
  }
  if (k < 0){
      k = latticeSize - 1;
  }
  if (i > latticeSize - 1){
      i = 0;
  }
  if (j > latticeSize - 1){
      j = 0;
  }
  if (k > latticeSize - 1){
      k = 0;
  }
  return latticeSize * latticeSize * i + latticeSize * j + k;
}

double Lattice::configurationEnergy(int m, int s){
    double energy = 0;
    Site testSite = lat[m];
    for (int i = 0; i < NUMNEIGHBOR; ++i){
      energy += s * lat[testSite.nnIndex[i]].spin;
    }
    return isingStrength * energy;
}
//
// void Lattice::linearMcIteration(double temperature){
//   double randNum;
//   double transitionProbability;
//   double initEnergy, flipEnergy, energyDiff;
//   // randomly pick iterations number of sites sites and determine wheather to flip them
//   // based on their boltzmann factor.
//
//   for (int i = 0; i <= volume; ++i){
//     initEnergy = configurationEnergy(i, lat[i].spin);
//     //Flip site and take energy difference
//     lat[i].spin *= -1;
//     flipEnergy = configurationEnergy(i, lat[i].spin);
//     energyDiff = flipEnergy - initEnergy;
//
//     if (energyDiff < 0){
//       continue;
//     } else {
//       randNum = prng.randDblExc();
//       transitionProbability = exp(-energyDiff / temperature);
//
//       if (randNum < transitionProbability){
//         continue;
//       } else {
//         lat[i].spin *= -1;
//       }
//     }
//   }
// }

void Lattice::randomMcIteration(double temperature){
  int randIndex;
  double randNum;
  double transitionProbability, energyDiff;
  // randomly pick iterations number of sites sites and determine wheather to flip them
  // based on their boltzmann factor.

  for (int i = 0; i <= volume; ++i){
    randIndex = (int)prng.randInt(volume);
    energyDiff = configurationEnergy(randIndex, -lat[randIndex].spin) - configurationEnergy(randIndex, lat[randIndex].spin);

    if (energyDiff <= 0){
      lat[randIndex].spin *= -1;
    } else {
        randNum = prng.randDblExc();
        transitionProbability = exp(-(energyDiff) / temperature);
        if (randNum < transitionProbability){
          lat[randIndex].spin *= -1;
       } 
    }
  }
}

void Lattice::warmupSweep(int iterations, double temperature){
  for (int i = 0; i < iterations; ++i){
    randomMcIteration(temperature);
  }
}
