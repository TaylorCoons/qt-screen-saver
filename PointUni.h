#ifndef PointUni_h
#define PointUni_h

class PointUni : public PointDist {


    /* Functions */
    public:
    // Ctor
    PointUni() {
    }
    
    Point Generate() {
        Point p;
        p.x = rand() % (maxX - minX) + minX;
        p.y = rand() % (maxY - minY) + minY;
        return p;
    }

    // Dtor
    ~PointUni() {
    }

};

#endif
