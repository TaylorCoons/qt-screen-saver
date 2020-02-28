#include <X11/Xlib.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "vroot.h"

#include "QTree.h"


struct Point {
    double x;
    double y;
};

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

    while (true) {
       
        
        // Clear screen 
        // XClearWindow(pDisplay, root);
        
        // Add Point
        Point p;
        p.x = rand() % width;
        p.y = rand() % height;
        points.push_back(p);
      
        XColor brush;
        brush.red = rand() % 0xffff;
        brush.green = rand() % 0xffff;
        brush.blue = rand() % 0xffff;

        XSetForeground(pDisplay, gc, brush.pixel); 

        unsigned int last = points.size() - 1;
        qt.Insert(points[last].x, points[last].y, &points[last]);
    
        // Draw points
        XDrawArc(pDisplay, root, gc, points[last].x, points[last].y, 2, 2, 0, 6.262);

        // Draw QTree
        qt.Draw(pDisplay, &root, &gc);

        // Swap buffers
        XFlush(pDisplay);

        // Pause
        usleep(100000); 

    }  

    XCloseDisplay(pDisplay);
 
    return 0;
}
