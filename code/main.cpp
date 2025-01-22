#include <iostream>
#include <string>
#include "Coordinate.h"
#include <SFML/Graphics.hpp>
#include "Pieces.h"
#include "types.h"
#include "Board.h"

#define X1 Coordinate(1,0)
#define Y1 Coordinate(0,1)

using namespace std;



int main() {

    int wx = 800;
    int wy = 800;

    sf::RenderWindow window(sf::VideoMode(wx, wy), "Schaken");

    
   while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Cyan);
        int number = 0;
        for (size_t y = 0; y < 8; y++)
        {
            number = y;
            for (size_t x = 0; x < 8; x++)
            {
                sf::RectangleShape shape(sf::Vector2f(100,100));
                shape.setPosition(sf::Vector2f(100 * x,100 * y));
                if (number % 2 == 1){
                    shape.setFillColor(sf::Color::Black);                
                }
                else{
                    shape.setFillColor(sf::Color::White);
                }
                window.draw(shape);
                number++;
            }
        }       
        window.display();
    }
    return 0;
}
