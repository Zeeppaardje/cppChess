

#ifndef BOARD
#define BOARD

#include <unordered_map>
#include "Pieces.h"
#include "Coordinate.h"
#include "types.h"
#include "ActionHandler.h"

class Piece;
class ActionHandler;

class Board{
    private:
        std::unordered_map<Coordinate,Piece*,HashFunction>* pieces; 
        Piece* selectedPiece;
        int turn;
        int playerAmount;
        actionState state;
        std::unordered_map<actionState,ActionHandler*>* actions;
    public:
        Board(Coordinate bounds);
        ~Board();
        Coordinate bounds;
        void nextPlayer();
        void action(Coordinate mouse);
        /* setters en gettes */
        std::unordered_map<Coordinate,Piece*,HashFunction>* getPieces() const;
        void addPiece(Piece* piece);
        void removePiece(Coordinate pos);
        int getTurn() const;
        void setTurn(int t);
        Piece* getSelectedPiece();
        void setSelectedPiece(Piece* p); 
        actionState getState() const;
        void setState(actionState state);
};

#endif