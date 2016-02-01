#include <iostream>
#include <cmath>

#include "lattice.h"
#include "datautils.h"

using namespace std;
//------------------------------------------------------------------systemEnergy
//Calculate and return the total energy of the system normalized by the size of
//the system.
double systemEnergy(Lattice lattice){
  double totalEnergy = 0; // Total energy of the lattice

  // Calculate the energy of the site i, for all i in the volume of the system.
  // We do this by calculating the configuration energy of the site i and its nearest
  // neighbors in the lattice.
  for (int i = 0; i < lattice.volume; ++i){
    totalEnergy += lattice.configurationEnergy(i, lattice.lat[i].spin);
  }
  return totalEnergy;
}

//-----------------------------------------------------------systemMagnetization
//Calculate and return the total magnetization of the system normalized by the size of
//the system.
double systemMagnetization(const Lattice lattice){
  double totMag = 0;

  // grab the spin of the site i, for all i in the volume of the system.
  for (int i = 0; i < lattice.volume; ++i){
    totMag += lattice.lat[i].spin;
  }
  return totMag;
}

void collectMcData(Lattice lattice, int iterations, double temperature){
  double sampleMagnetization, sampleEnergy;

  double avgEnergy = 0;
  double avgEnergySquare = 0;
  double avgMagnet = 0;
  double avgMagnetSquare = 0;

  for (int i = 0; i < iterations; ++i){
    lattice.randomMcIteration(temperature);
    sampleEnergy = systemEnergy(lattice);
    sampleMagnetization = systemMagnetization(lattice);

    avgEnergy += sampleEnergy;
    avgEnergySquare += sampleEnergy * sampleEnergy;
    avgMagnet += sampleMagnetization;
    avgMagnetSquare += sampleMagnetization * sampleMagnetization;
  }

  //output
  avgEnergy       /= ((double)iterations);
  avgEnergySquare /= ((double)iterations);
  avgMagnet       /= ((double)iterations);
  avgMagnetSquare /= ((double)iterations);

  cout << temperature / 4.51  << "\t"<< avgEnergy  << "\t"<< fabs(avgMagnetSquare) << "\t"
       << (avgEnergySquare - avgEnergy * avgEnergy) / (temperature * temperature) << "\t"
       << (avgMagnetSquare - avgMagnet * avgMagnet) / temperature << "\t"
       << iterations <<endl;
}
