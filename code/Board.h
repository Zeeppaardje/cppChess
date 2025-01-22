#include <vector>
#include "Pieces.h"
#include "Coordinate.h"
#include "types.h"

#ifndef BOARD
#define BOARD



class Board{
    private:
        std::vector<Piece> pieces;     
        Coordinate bounds;
    public:
        Board(Coordinate bounds);
        std::vector<Piece> getPieces();
        void addPiece(Piece piece);
        void removePiece(Piece piece);
};

#endif