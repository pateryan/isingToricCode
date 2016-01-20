 // Test program for the lattice and site classes

#include <iostream>
#include <fstream>

#include "site.h"
#include "MersenneTwister.h"
#include "lattice.h"

// function prototypes
void readInput(int, char **, int*, int*, int*);

// namespace call -- narrow down to only functions I use later...
using namespace std;

int main(int argc, char *argv[])
{
  // Initialize the lattice size and the random number generator
  int xLen, yLen, zLen;
  readInput(argc, argv, &xLen, &yLen, &zLen);
  MTRand prng;

  // Initialize the lattice with random spins, and allocate the nearest neighbor
  // data structure.
  Lattice lat(xLen, yLen, zLen);

  return 0;
}

/*****************************HELPER FUNCTIONS*********************************/

// Read in the input file as a program argument. Currently, the init function
// will read in the x, y, and z dimensions of the lattice, assigning them to
// previously allocated integers.

void readInput(int argc, char *argv[], int *x, int *y, int *z){
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
    }
  }
}
