#ifndef PointNorm_h
#define PointNorm_h

#include <cmath>
#define PI 3.14159

#include "PointDist.h"

class PointNorm : public PointDist {

    /* Functions */
    public:
    // Ctor
    PointNorm() {
    
    }

    Point Generate() {
        int xRange = maxX - minX;
        int yRange = maxY - minY;
        double x = static_cast<double>(rand()) / static_cast<double>(RAND_MAX); 
        double y = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        double xNorm = sqrt(-2.0*log(x))*cos(2.0*PI*y);
        double yNorm = sqrt(-2.0*log(x))*sin(2.0*PI*y);
        xNorm = xNorm * static_cast<double>(xRange) / 5.0 + static_cast<double>(xRange) / 2.0;
        yNorm = yNorm * static_cast<double>(yRange) / 5.0 + static_cast<double>(yRange) / 2.0; 
        Point p;
        p.x = static_cast<int>(xNorm);
        p.y = static_cast<int>(yNorm);
        return p;
    }

    // Dtor
    ~PointNorm() {

    } 

};

#endif
