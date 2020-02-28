#include <SFML/Graphics.hpp>
#include <string>

#include "QTree.h"


int main(int argc, char* argv[])
{
    unsigned int numPoints = 0;
    if (argv[1] == nullptr) {
        return -1;
    }
    try {
       numPoints = std::stoi(argv[1]); 
    } catch (std::invalid_argument e) {
        return -1;        
    }
    const unsigned int width = 800;
    const unsigned int height = 800;
    sf::CircleShape points[numPoints];
    for (unsigned int i = 0; i < numPoints; i++) {
        points[i].setRadius(1);
        points[i].setFillColor(sf::Color::White);
        points[i].setPosition(sf::Vector2f(rand() % width, rand() % height)); 
    } 

    QTree<sf::CircleShape> qt(0, 0, width, height, 4);

    for (unsigned int i = 0; i < numPoints; i++) {
        sf::Vector2f pos = points[i].getPosition(); 
        qt.Insert(pos.x, pos.y, &points[i]);
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw points
        for (unsigned int i = 0; i < numPoints; i++) {
            window.draw(points[i]);
        }

        // Draw QTree
        qt.Draw(&window);

        window.display();
    }

    return 0;
}
