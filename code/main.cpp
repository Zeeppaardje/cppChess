#include <iostream>
#include <string>
#include <unordered_set>
#include "Coordinate.h"
#include <SFML/Graphics.hpp>
#include "Pieces.h"
#include "types.h"
#include "Board.h"
#include "math.h"
#include "fileReader.h"

#define X1 Coordinate(1,0)
#define Y1 Coordinate(0,1)

using namespace std;


int main() {

    int wx = 800;
    int wy = wx;

    int mouseX = -1;
    int mouseY = -1;

    int bordHeight = 8;
    int tileSize = wx / bordHeight;

    Board* board = readBoard("saves/default.txt");

    Piece* clickedPiece = NULL;

    sf::RenderWindow window(sf::VideoMode(wx, wy), "Schaken");

    
   while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved){
                mouseX = floor(event.mouseMove.x / tileSize);
                mouseY = floor(event.mouseMove.y / tileSize);
            }

            if (event.type == sf::Event::MouseButtonPressed){
                
                if (clickedPiece){
                    if (Coordinate(mouseX,mouseY) == clickedPiece->getPosition()){
                        clickedPiece = nullptr;
                    }
                }
                else if (board->getPieces()->find(Coordinate(mouseX,mouseY)) != board->getPieces()->end()){
                    clickedPiece = board->getPieces()->at(Coordinate(mouseX,mouseY));
                }
                else{
                    clickedPiece = NULL;
                }
            }
            
        }

        window.clear(sf::Color::Cyan);
        int number = 0;
        // maak bord
        for (size_t y = 0; y < bordHeight; y++)
        {
            number = y;
            for (size_t x = 0; x < bordHeight; x++)
            {
                
                sf::RectangleShape shape(sf::Vector2f(tileSize,tileSize));
                shape.setPosition(sf::Vector2f(tileSize * x,tileSize * y));
                if (x == mouseX && y == mouseY){
                    shape.setFillColor(sf::Color::Green);
                }
                else if (number % 2 == 1){
                    shape.setFillColor(sf::Color(118,150,86));                
                }
                else{
                    shape.setFillColor(sf::Color(238,238,210));
                }
                window.draw(shape);
                number++;
            }
        }

        for (size_t y = 0; y < bordHeight; y ++) {
            for (size_t x = 0; x < bordHeight; x++) {
                //render pieces
                if (board->getPieces()->find(Coordinate(x,y)) != board->getPieces()->end()){
                    Piece* piece = board->getPieces()->at(Coordinate(x,y));
                    sf::Texture texture;
                    if (!texture.loadFromFile(piece->getImagePath())){
                        cout << "Could not load " << piece->getImagePath();
                        return 1;
                    }
                    sf::Sprite sprite;
                    
                    sprite.setTexture(texture);
                    sprite.setOrigin(sf::Vector2f(64,64));
                    sprite.setPosition(tileSize * x + tileSize / 2,tileSize * y + tileSize / 2);
                    //sprite.setOrigin(0,0);
                    window.draw(sprite);
                }
            }
        }
        // render moves
        if (clickedPiece){
            
            auto moves = clickedPiece->possible_moves();
            for (Coordinate pos : moves){
                sf::CircleShape moveCircle(20);
                moveCircle.setOrigin(moveCircle.getRadius(),moveCircle.getRadius());
                moveCircle.setFillColor(sf::Color::Red);
                
                moveCircle.setPosition(sf::Vector2f(tileSize * pos.x + tileSize / 2, tileSize * pos.y + tileSize / 2));
                window.draw(moveCircle);
            }
        }
        window.display();
        window.clear();
    }
    return 0;
}
