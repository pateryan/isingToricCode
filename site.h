/* Header file for Site class. See source file for function description */

#ifndef SITE_H
#define SITE_H

#define NUMNEIGHBOR 6
#define XLEN 20
#define YLEN 20
#define ZLEN 20

class Site{
    public:
        int spin;
        int nnIndex[NUMNEIGHBOR];

        Site();
        Site(int*, int);
        void readNeighbor(void);
};

#endif /* SITE_H */
