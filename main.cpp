#include <X11/Xlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <cmath>
#define PI 3.14159265

#include "vroot.h"

#include "QTree.h"


struct Point {
    double x;
    double y;
};


unsigned long int CreateColor(int red, int green, int blue) {
    return (red << 16) + (green << 8) + blue;
}


int main(int argc, char* argv[])
{
    
    unsigned int width = 800;
    unsigned int height = 800;
       
    // Open the display
    Display* pDisplay = XOpenDisplay(getenv("DISPLAY"));

    // Get a handle to the root window
    Window root = DefaultRootWindow(pDisplay);

    // Create graphics context
    GC gc = XCreateGC(pDisplay, root, 0, NULL);

    Window windowReturn;
    int x;
    int y;
    unsigned int border;
    unsigned int depth;
    XGetGeometry(pDisplay, root, &windowReturn, &x, &y, &width, 
                      &height, &border, &depth);

    width = width - border - x - 2;
    height = height - border - y - 2;

    QTree<Point> qt(0, 0, width, height, 4);
    
    std::vector<Point> points;
    
    // Set screen to black
    XSetForeground(pDisplay, gc, WhitePixelOfScreen(DefaultScreenOfDisplay(pDisplay))); 

    // Create QTree color
    unsigned long int qtColor = CreateColor(167, 30, 130);

    while (true) {
       
        
        // Clear screen 
        // XClearWindow(pDisplay, root);
        
        // Add Point
        // Point p;
        // p.x = rand() % width;
        // p.y = rand() % height;
        // points.push_back(p);

        // Generate normally distributed point
        double x = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        double y = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        double xNorm = sqrt(-2.0*log(x))*cos(2.0*PI*y);
        double yNorm = sqrt(-2.0*log(x))*sin(2.0*PI*y);
        xNorm = xNorm * static_cast<double>(width) / 10.0 + static_cast<double>(width) / 2.0;
        yNorm = yNorm * static_cast<double>(height) / 10.0 + static_cast<double>(height) / 2.0;
        
        Point p;
        p.x = static_cast<int>(xNorm);
        p.y = static_cast<int>(yNorm);
        points.push_back(p);
    
        // Create point color 
        unsigned long int ptColor = CreateColor(rand() % 255, rand() % 255, rand() % 255);
 
        unsigned int last = points.size() - 1;
        qt.Insert(points[last].x, points[last].y, &points[last]);
    
        // Draw points
        XSetForeground(pDisplay, gc, ptColor); 
        XDrawArc(pDisplay, root, gc, points[last].x, points[last].y, 2, 2, 0, 6.262);

        // Draw QTree
        XSetForeground(pDisplay, gc, qtColor); 
        qt.Draw(pDisplay, &root, &gc);

        // Swap buffers
        XFlush(pDisplay);

        // Pause
        usleep(100000); 

    }  

    XCloseDisplay(pDisplay);
 
    return 0;
}
