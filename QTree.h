#ifndef QTree_h
#define QTree_h

#include <SFML/Graphics.hpp>

template<typename T>
class QTree {

    /* Variables */
    public:
    
    private:
    // Object point pairing
    struct Object {
        double x;
        double y;
        T* pObj;
    };

    // SFML Visual Object
    sf::RectangleShape* rect;
   
    // Bounding box 
    double x;
    double y;
    double width;
    double height;
    // Capacity
    unsigned int capacity;
    // Size
    unsigned int size;
    // Number of nodes
    static const unsigned int numNodes = 4;

    // Flag to check if it has children
    bool hasChildren = false;
    
    // Node assignments
    enum QUAD {
        NE,
        NW,
        SE,
        SW
    };

    // Array of object pointers to store
    Object* objects;

    // Array of QTree Pointers for the nodes
    QTree* nodes[numNodes];

    /* Functions */
    public:
    
    // Ctor
    QTree(double x, double y, double width, double height, unsigned int capacity) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height; 
        this->capacity = capacity;
        size = 0;
        
        // Create an array of objects
        objects = new Object[capacity]; 

        // Create the visual rectangle representation
        rect = new sf::RectangleShape();
        double thickness = 1.0;
        rect->setPosition(x + thickness, y + thickness);
        rect->setSize(sf::Vector2f(width - 2.0 * thickness, height - 2.0 * thickness));
        rect->setOutlineColor(sf::Color::Blue);
        rect->setOutlineThickness(thickness); 
        rect->setFillColor(sf::Color(0, 0, 0, 0));
    }

    // Insert point (object overload)
    void Insert(Object object) {
        Insert(object.x, object.y, object.pObj);
    }

    // Insert point
    void Insert(double x, double y, T* pObj) {
        if (!hasChildren && size >= capacity) {
            double halfWidth = width / 2.0;
            double halfHeight = height / 2.0;
            // First create the new QTrees
            nodes[NE] = new QTree(this->x + halfWidth, this->y, halfWidth, halfHeight, capacity);
            nodes[NW] = new QTree(this->x, this->y, halfWidth, halfHeight, capacity);
            nodes[SE] = new QTree(this->x + halfWidth, this->y + halfHeight, halfWidth, halfHeight, capacity);
            nodes[SW] = new QTree(this->x, this->y + halfHeight, halfWidth, halfHeight, capacity);
             
            // Move our objects to our new QTrees
            for (unsigned int i = 0; i < capacity; i++) {
                QUAD quad = FindQuad(objects[i].x, objects[i].y);
                nodes[quad]->Insert(objects[i]);     
            }
            hasChildren = true;
        } else if (hasChildren) {
            QUAD quad = FindQuad(x, y);
            nodes[quad]->Insert(x, y, pObj);
        } else {
            // Just insert object into the array
            objects[size] = {x, y, pObj};
            size++;
        }
    }
    
    // Draw the Quadtree
    void Draw(sf::RenderWindow* pWindow) {
        pWindow->draw(*rect);
        if (hasChildren) {
            for (unsigned int i = 0; i < numNodes; i++) {
                nodes[i]->Draw(pWindow);
            }
        }
    }

    // Dtor
    ~QTree() {
        if (objects != nullptr) {
            delete[] objects;
            objects = nullptr;
        }
    }

    private:
    QUAD FindQuad(double x, double y) {
        if (x < this->x + width / 2.0) {
            if (y < this->y + height / 2.0) {
                return NW;
            } else {
                return SW;
            }
        } else {
            if (y < this->y + height / 2.0) {
                return NE;
            } else {
                return SE;
            }
        }
    } 

};


#endif
