#ifndef PointDist_h
#define PointDist_h

#include <random>
#include <ctime>

class PointDist {

    /* Variables */
    public:
    // Point Structure
    struct Point {
        int x;
        int y;
    };

    protected:
    int minX;
    int maxX;
    int minY;
    int maxY; 
    
    /* Functions */
    public:
    // Ctor
    PointDist() {
        srand(time(0));
    }
    
    void setXRange(int minX, int maxX) {
        this->minX = minX;
        this->maxX = maxX;
    }
    void setYRange(int minY, int maxY) {
        this->minY = minY;
        this->maxY = maxY;
    }

    virtual Point Generate() = 0;

    // Dtor
    ~PointDist() {
    }
};


#endif
