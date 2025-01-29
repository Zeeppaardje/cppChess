

#ifndef BOARD
#define BOARD

#include <unordered_map>
#include "Pieces.h"
#include "Coordinate.h"
#include "types.h"


class Piece;


class Board{
    private:
        std::unordered_map<Coordinate,Piece*,HashFunction>* pieces; 
    public:
        Board(Coordinate bounds);
        ~Board();
        Coordinate bounds;
        std::unordered_map<Coordinate,Piece*,HashFunction>* getPieces() const;
        void addPiece(Piece* piece);
        void removePiece(Coordinate pos);
};

#endif