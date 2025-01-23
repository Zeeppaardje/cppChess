#include <unordered_map>
#include "Pieces.h"
#include "Coordinate.h"
#include "types.h"

#ifndef BOARD
#define BOARD



class Board{
    private:
        std::unordered_map<Coordinate,Piece*,HashFunction>* pieces; 
    public:
        Board(Coordinate bounds);
        Coordinate bounds;
        std::unordered_map<Coordinate,Piece*,HashFunction>* getPieces() const;
        void addPiece(Piece* piece);
        void removePiece(Coordinate pos);
};

#endif