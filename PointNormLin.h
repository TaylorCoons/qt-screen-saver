#ifndef PointNormLin_h
#define PointNormLin_h

#include <cmath>
#include <random>
#define PI 3.14159

#include "PointDist.h"

class PointNormLin : public PointDist {

    /* Variables */
    private:
    std::default_random_engine generator;
    std::normal_distribution<double> norm;

    /* Functions */
    public:
    // Ctor
    PointNormLin() :
    norm(0.0, 1.0), generator(time(0)) {
        srand(time(0));
    }

    Point Generate() {
        double xRange = static_cast<double>(maxX - minX);
        double yRange = static_cast<double>(maxY - minY);
        double slope = yRange / xRange;
        double normVal = norm(generator);
        Point p;
        p.x = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * xRange;
        p.y = static_cast<double>(p.x) * slope + normVal * (yRange / 10.0);       
 
        return p;
    }

    // Dtor
    ~PointNormLin() {

    }


};

#endif
