#include <iostream>
#include <string>
#include <unordered_set>
#include "Coordinate.h"
#include <SFML/Graphics.hpp>
#include "Pieces.h"
#include "types.h"
#include "Board.h"
#include "math.h"

#define X1 Coordinate(1,0)
#define Y1 Coordinate(0,1)

using namespace std;



int main() {

    int wx = 800;
    int wy = 800;

    int mouseX = -1;
    int mouseY = -1;

    int bordHeight;
    int bordWidth;

    Board board(Coordinate(bordWidth,bordHeight));

    Piece* clickedPiece = NULL;
    Piece* pawn = new Pawn(Coordinate(4,1),WHITE,board.bounds);
    Piece* pawn2 = new Pawn(Coordinate(1,1),WHITE,board.bounds);
    Piece* pawn3 = new Pawn(Coordinate(3,1),WHITE,board.bounds);   
    board.addPiece(pawn);
    board.addPiece(pawn2);
    board.addPiece(pawn3);
    sf::RenderWindow window(sf::VideoMode(wx, wy), "Schaken");

    
   while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved){
                mouseX = floor(event.mouseMove.x / 100);
                mouseY = floor(event.mouseMove.y / 100);
            }

            if (event.type == sf::Event::MouseButtonPressed){
 
                if (board.getPieces()->find(Coordinate(mouseX,mouseY)) != board.getPieces()->end()){
                    clickedPiece = board.getPieces()->at(Coordinate(mouseX,mouseY));
                }
                else{
                    clickedPiece = NULL;
                }
            }
        }

        window.clear(sf::Color::Cyan);
        int number = 0;
        // maak bord
        for (size_t y = 0; y < 8; y++)
        {
            number = y;
            for (size_t x = 0; x < 8; x++)
            {
                
                sf::RectangleShape shape(sf::Vector2f(100,100));
                shape.setPosition(sf::Vector2f(100 * x,100 * y));
                if (x == mouseX && y == mouseY){
                    shape.setFillColor(sf::Color::Green);
                }
                else if (number % 2 == 1){
                    shape.setFillColor(sf::Color::Black);                
                }
                else{
                    shape.setFillColor(sf::Color::White);
                }
                window.draw(shape);
                number++;
            }
        }
        for (size_t y = 0; y < 8; y ++) {
            for (size_t x = 0; x < 8; x++) {
                //render pieces
                if (board.getPieces()->find(Coordinate(x,y)) != board.getPieces()->end()){
                    Piece* piece = board.getPieces()->at(Coordinate(x,y));
                    sf::Texture texture;
                    if (!texture.loadFromFile(piece->getImagePath())){
                        cout << "Could not load " << piece->getImagePath();
                        return 1;
                    }
                    sf::Sprite sprite;
                    
                    sprite.setTexture(texture);
                    sprite.setPosition(100 * x,100 * y);
                    
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
                
                moveCircle.setPosition(sf::Vector2f(100 * pos.x + 50, 100 * pos.y + 50));
                window.draw(moveCircle);
            }
        }
        window.display();
        window.clear();
    }
    return 0;
}
