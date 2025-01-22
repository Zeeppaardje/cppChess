#include "Pieces.h"
#include "Coordinate.h"
#include "types.h"
#include <vector>
#include <unordered_set>

Piece::Piece(Coordinate position, piece_color color, Coordinate bounds)
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
    return this->getColor();
}

void Piece::setPosition(const Coordinate & position)
{
    this->position = position;
}


// PAWN

Pawn::Pawn(Coordinate pos, piece_color color,Coordinate bounds) : Piece(pos,color,bounds)
{
    this->name = "PAWN";
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
        if (y <= this->bounds.y && y >= 0)
            moves.insert(Coordinate(this->position.x,y));
    }
    return moves;
}
