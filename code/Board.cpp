#include "Board.h"
#include <unordered_map>
#include "Pieces.h"
#include "Coordinate.h"
#include "hashFunctions.h"
#include "types.h"


Board::Board(Coordinate bounds)
{
    this->bounds = bounds;
    this->pieces = new std::unordered_map<Coordinate,Piece*,HashFunction>;
}

Board::~Board()
{

    for (auto it = this->pieces->begin(); it != this->pieces->end(); it++)
    {
        delete it->second;
    }
    delete pieces;
}
std::unordered_map<Coordinate, Piece*, HashFunction>* Board::getPieces() const
{
    return this->pieces;
}

void Board::addPiece(Piece* piece)
{
    if (!piece){
        return;
    }
    (*this->pieces)[piece->getPosition()] = piece;
    piece->setBound(this->bounds);
    piece->setBoard(this);
}

void Board::removePiece(Coordinate pos)
{
    if (pos.x < this->bounds.x && pos.x > 0 && pos.y < this->bounds.y && pos.y > 0) {
        Piece* piece = this->pieces->at(pos);
        delete piece;
        piece = NULL;
        this->pieces->erase(pos);
    }
}
