#include "Coordinate.h"
#include <unordered_set>
#include "types.h"

#ifndef PIECE
#define PIECE

struct HashFunction {
    size_t operator()(const Coordinate& coord) const {
        std::string str = coord.toString();
        return std::hash<std::string>()(str);
    }
};


class Piece{
    protected:
        Coordinate position;
        piece_color color;
        std::string name;
        Coordinate bounds;
        std::string imagePath;
    public:
        
        Piece(Coordinate position,piece_color color,Coordinate bounds);
        ~Piece();
        Coordinate  getPosition() const;
        piece_color getColor() const;
        std::string getImagePath() const;
        void setPosition(const Coordinate&);
        void setBound(Coordinate bound);
        virtual std::unordered_set<Coordinate,HashFunction> possible_moves() = 0;    
};


class Pawn: public Piece{
    private:
        bool firstMove;
    public:
        Pawn(Coordinate pos,piece_color color,Coordinate bounds);
        virtual std::unordered_set<Coordinate,HashFunction> possible_moves();       
};

#endif