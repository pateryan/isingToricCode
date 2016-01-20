/* Source file for the Site class and associated methods
 *
 * Patrick Ryan
 * Created: 14/01/16
 *
 * The site class describes a site on a lattice subjected to a Monte Carlo
 * simulation. The class gives constant time access to nearest neighbors on an n
 * dimensional lattice, as well as the state of the site.
 *
 * Site object patameters:
 *
 * nearSites            int[6]     Array of pointers to nearest neighbor sites.
 *          The ordering of the sites is x left, x right, y above, y below, z
 *          in front, z behind.
 * isSpinUp:            bool        True if state is spin up, false otherwise
 *
 * NOTE: if a site does not have a nearest neighbor, a nullptr is assigned in
 * its place
 *
 * Site object methods:
 *
 * Site()                                   Default constructor
 * Site(Site *nearSites[], bool isSpinUp)   Full Constructor
 *
 */
#include <iostream>
#include "site.h"

Site::Site(){
    //Default the spin of a site to spin up and no nearest neighbors
    spin = 1;
    nnIndex[NUMNEIGHBOR] = {0};
}

Site::Site(int neighbors[], int s){
    spin = s;
    for(int i = 0; i < NUMNEIGHBOR; ++i){
        nnIndex[i] = neighbors[i];
    }
}

void Site::readNeighbor(void){
    for(int i = 0; i < NUMNEIGHBOR; ++i){
        std::cout << nnIndex[i] << std::endl;
    }
}
