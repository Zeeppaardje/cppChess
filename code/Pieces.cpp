#include "Pieces.h"
#include "Coordinate.h"
#include "types.h"
#include <vector>
#include <unordered_set>


Piece::Piece(Coordinate position, piece_color color)
{
    this->position = position;
    this->bounds = bounds;
    this->color = color;
}

Piece::~Piece()
{

}

Coordinate Piece::getPosition() const
{
    return this->position;
}

piece_color Piece::getColor() const
{
    return this->color;
}

std::string Piece::getImagePath() const
{
    static std::string enumToString[2] = {"white","black"};
    return "sprites/" + enumToString[this->color] + '-' + this->name + ".png";
}

void Piece::setPosition(const Coordinate & position)
{
    this->position = position;
}

void Piece::setBound(Coordinate bound)
{
    this->bounds = bound;
}

void Piece::setBoard(Board *board)
{
    this->board = board;
}

Board* Piece:: getBoard() const{
    return this->board;
}



bool validCoordinate(Board* board,Coordinate coord,piece_color c){
    /* position out of board*/
    if (coord.x >= board->bounds.x || coord.x < 0 || coord.y >= board->bounds.y || coord.y < 0){
        return false;
    }

    /*place taken bij piece of same color*/
    if (board->getPieces()->find(coord) != board->getPieces()->end() && board->getPieces()->at(coord)->getColor() == c){
        return false;
    }
    return true;
}

// PAWN

Pawn::Pawn(Coordinate pos, piece_color color) : Piece(pos,color)
{
    this->name = "pawn";
    this->firstMove = true;
}

std::unordered_set<Coordinate,HashFunction> Pawn::possible_moves()
{
    static std::vector<Coordinate> color_direction = {Coordinate(0,1),Coordinate(0,-1)};

    std::unordered_set<Coordinate,HashFunction> moves;
    int steps = 1;
    if (this->firstMove){
        steps = 2;
    }
    for (int i = 1; i <= steps; i ++){
        int y = this->position.y + i * color_direction[this->color].y;
        Coordinate newCoord(this->position.x,y);
        if (validCoordinate(this->board,newCoord,this->color)){
            moves.insert(newCoord);
        }
    }
    return moves;
}

/*KING*/

King::King(Coordinate pos, piece_color color) : Piece(pos,color)
{   
    this->name = "king"; 
}
std::unordered_set<Coordinate, HashFunction> King::possible_moves()
{   

    std::unordered_set<Coordinate,HashFunction> moves;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {

            Coordinate newCoord(this->position.x + i,this->position.y + j);
            if (validCoordinate(this->board,newCoord,this->color)){
                moves.insert(newCoord);
            }
        }
        
    }
    return moves;
}


Queen::Queen(Coordinate pos, piece_color color) : Piece(pos,color)
{
    this->name = "queen";
}

std::unordered_set<Coordinate, HashFunction> Queen::possible_moves()
{
    return std::unordered_set<Coordinate, HashFunction>();
}

Rook::Rook(Coordinate pos, piece_color color) : Piece(pos,color)
{
    this->name = "rook";
}

std::unordered_set<Coordinate, HashFunction> Rook::possible_moves()
{
    return std::unordered_set<Coordinate, HashFunction>();
}

Bishop::Bishop(Coordinate pos, piece_color color) : Piece(pos,color)
{
    this->name = "bishop";
}

std::unordered_set<Coordinate, HashFunction> Bishop::possible_moves()
{
    return std::unordered_set<Coordinate, HashFunction>();
}

Knight::Knight(Coordinate pos, piece_color color) : Piece(pos,color)
{
    this->name = "knight";
}

std::unordered_set<Coordinate, HashFunction> Knight::possible_moves()
{
    std::unordered_set<Coordinate,HashFunction> moves;

    for (size_t x = 1; x <= 2; x++)
    {
        for (size_t y = 1; y <= 2; y++)
        {
            if (x != y)
                for (int i = -1; i < 2; i += 2){
                    for (int j = -1; j < 2; j += 2){
                        Coordinate newCoord(this->position.x + i * x,this->position.y + j * y);
                        if (validCoordinate(this->board,newCoord,this->color)){
                            moves.insert(newCoord);
                        }
                    }
            }
        }
        
    }
    
    return moves;
}
