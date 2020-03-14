#ifndef PointHalo_h
#define PointHalo_h

#include <cmath>
#include <random>
#define PI 3.14159

#include "PointDist.h"

class PointHalo : public PointDist {

    /* Variables */
    private:
    std::default_random_engine generator;
    std::normal_distribution<double> norm;


    /* Functions */
    public:
    // Ctor
    PointHalo() :
    norm(1.0, 0.2), generator(time(0)) {
        srand(time(0));
    }

    Point Generate() {
        double diff = norm(generator);
        double angle = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * 2.0 * PI;
        double xRange = static_cast<double>(maxX - minX);
        double yRange = static_cast<double>(maxY - minY);
        Point center;
        center.x = xRange / 2.0 + static_cast<double>(minX);
        center.y = yRange / 2.0 + static_cast<double>(minY);
        double radiusX = xRange / 2.4;
        double radiusY = yRange / 2.4; 
        Point p;
        p.x = (radiusX*diff)*cos(angle) + center.x;
        p.y = (radiusY*diff)*sin(angle) + center.y;
        return p; 
    }
    
    // Dtor
    ~PointHalo() {

    }

};

#endif
