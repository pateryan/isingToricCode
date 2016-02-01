 // Test program for the lattice and site classes

#include <iostream>
#include <string>
#include <cmath>

#include "site.h"
#include "MersenneTwister.h"
#include "lattice.h"
#include "datautils.h"

// function prototypes
void readInput(int, char **, int*, double*);

// namespace call -- narrow down to only functions I use later...
using namespace std;

int main(int argc, char *argv[])
{
  // Initialize the lattice size and the random number generator
  int latSize;
  double temperature;
  readInput(argc, argv, &latSize, &temperature);
  MTRand prng;

  // Initialize the lattice with random spins, and allocate the nearest neighbor
  // data structure.
  Lattice lattice(latSize);

  lattice.warmupSweep(100000, temperature);
  collectMcData(lattice, 1000000, temperature);

  return 0;
}

/*****************************HELPER FUNCTIONS*********************************/

// Read in the input file as a program argument. Currently, the init function
// will read in the x, y, and z dimensions of the lattice, assigning them to
// previously allocated integers. It also takes in a temperature.

void readInput(int argc, char *argv[], int *latSize, double *temp){
  if (argc != 3){
    cout << "Usage: " << argv[0] << " LatticeSize temperature" << endl;
    exit(0);
  }
  else {
    *latSize = stoi(argv[1]);
    *temp = stod(argv[2]);
  }
}
