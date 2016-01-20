 // Test program for the lattice and site classes

#include <iostream>
#include <fstream>

#include "site.h"
#include "MersenneTwister.h"
#include "lattice.h"

// function prototypes
void readInput(int, char **, int*, int*, int*, double*);

// namespace call -- narrow down to only functions I use later...
using namespace std;

int main(int argc, char *argv[])
{
  // Initialize the lattice size and the random number generator
  int xLen, yLen, zLen;
  double temperature;
  readInput(argc, argv, &xLen, &yLen, &zLen, &temperature);
  MTRand prng;

  // Initialize the lattice with random spins, and allocate the nearest neighbor
  // data structure.
  Lattice lattice(xLen, yLen, zLen);
  lattice.monteCarloSweep(10000, temperature);


  // Test to ensure that the nearest neghbor allocation and configuration energy function
  // work as intended
  // for (int i = 0; i < xLen * yLen * zLen; ++i){
  //   cout << "Nearest neighbor indices for site " << i;
  //   for (int j = 0; j < NUMNEIGHBOR; ++j){
  //     cout << " " <<(lattice.lat[i]).nnIndex[j];
  //   }
  //   cout << " Configuration energy for the site " << lattice.configurationEnergy(i) << endl;
  // }

  return 0;
}

/*****************************HELPER FUNCTIONS*********************************/

// Read in the input file as a program argument. Currently, the init function
// will read in the x, y, and z dimensions of the lattice, assigning them to
// previously allocated integers. It also takes in a temperature.

void readInput(int argc, char *argv[], int *x, int *y, int *z, double *temp){
  if (argc != 2){
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    exit(0);
  }
  else {
    ifstream theFile(argv[1]);
    if (!theFile.is_open()){
      cout << "Could not read file" << endl;
      exit(1);
    }
    else {
      theFile >> *x;
      theFile >> *y;
      theFile >> *z;
      theFile >> *temp;
    }
  }
}
