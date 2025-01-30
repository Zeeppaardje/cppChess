


#ifndef Action
#define Action

#include "Board.hpp"
#include "Coordinate.hpp"

class Board;

class ActionHandler{
    public:
        virtual void onClick(Coordinate mouse,Board* board) = 0;
};

class SelectActionHandler: public ActionHandler{
    public:
        virtual void onClick(Coordinate mouse, Board* board);
};

class PlayActionHandler: public ActionHandler{
    public:
        virtual void onClick(Coordinate mouse, Board* board);
};

#endif