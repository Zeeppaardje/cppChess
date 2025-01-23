#include "Board.h"
#include <unordered_map>
#include "Pieces.h"
#include "Coordinate.h"
#include "types.h"


Board::Board(Coordinate bounds)
{
    this->bounds = bounds;
    this->pieces = new std::unordered_map<Coordinate,Piece*,HashFunction>;
}

std::unordered_map<Coordinate, Piece*, HashFunction>* Board::getPieces() const
{
    return this->pieces;
}

void Board::addPiece(Piece* piece)
{
    (*this->pieces)[piece->getPosition()] = piece;
    piece->setBound(this->bounds);
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
