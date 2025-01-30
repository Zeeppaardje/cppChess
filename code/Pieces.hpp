

#ifndef PIECE
#define PIECE

#include "Coordinate.hpp"
#include "hashFunctions.hpp"
#include <unordered_set>
#include "types.hpp"
#include "Board.hpp"

class Board;




class Piece{
    protected:
        Coordinate position;
        piece_color color;
        Coordinate bounds;
        Board* board;
        int move_count; /* voor pawn */
    public:
        std::string name;
        Piece(Coordinate position,piece_color color);
        ~Piece();
        void add_move_count();
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