

#ifndef PIECE
#define PIECE

#include "Coordinate.h"
#include "hashFunctions.h"
#include <unordered_set>
#include "types.h"
#include "Board.h"

class Board;




class Piece{
    protected:
        Coordinate position;
        piece_color color;
        std::string name;
        Coordinate bounds;
        Board* board;
    public:
        
        Piece(Coordinate position,piece_color color);
        ~Piece();
        Coordinate  getPosition() const;
        piece_color getColor() const;
        std::string getImagePath() const;
        void setPosition(const Coordinate&);
        void setBound(Coordinate bound);
        void setBoard(Board* board);
        Board* getBoard() const;
        virtual std::unordered_set<Coordinate,HashFunction> possible_moves() = 0;    
};


class Pawn: public Piece{
    private:
        bool firstMove;
    public:
        Pawn(Coordinate pos,piece_color color);
        virtual std::unordered_set<Coordinate,HashFunction> possible_moves();       
};


class King: public Piece{
    private:
    public:
        King(Coordinate pos,piece_color color);
        virtual std::unordered_set<Coordinate,HashFunction> possible_moves();
};

class Queen: public Piece{
    private:
    public:
        Queen(Coordinate pos,piece_color color);
        virtual std::unordered_set<Coordinate,HashFunction> possible_moves();
};

class Rook: public Piece{
    private:
    public:
        Rook(Coordinate pos,piece_color color);
        virtual std::unordered_set<Coordinate,HashFunction> possible_moves();
};

class Bishop: public Piece{
    private:
    public:
        Bishop(Coordinate pos,piece_color color);
        virtual std::unordered_set<Coordinate,HashFunction> possible_moves();
};


class Knight: public Piece{
    private:
    public:
        Knight(Coordinate pos,piece_color color);
        virtual std::unordered_set<Coordinate,HashFunction> possible_moves();
};


#endif