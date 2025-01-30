#include "ActionHandler.h"
#include <iostream>
#include <unordered_set>
#include "hashFunctions.h"

void SelectActionHandler::onClick(Coordinate mouse, Board *board)
{

    if (board->getPieces()->find(mouse) != board->getPieces()->end()){
        board->setSelectedPiece(board->getPieces()->at(mouse));
        board->setState(PLAY);
    }
    else{
        board->setSelectedPiece(nullptr);
    }
}

void PlayActionHandler::onClick(Coordinate mouse, Board *board)
{
    if (mouse == board->getSelectedPiece()->getPosition()){
        board->setSelectedPiece(nullptr);
        board->setState(SELECT);
        return;
    }

    // if (board->getPieces()->at(mouse)->getColor() == board->getSelectedPiece()->getColor()){
    //     board->setSelectedPiece(board->getSelectedPiece());
    //     return;
    // }

    std::unordered_set<Coordinate,HashFunction> moves = board->getSelectedPiece()->possible_moves();
    if (moves.find(mouse) != moves.end()){
        
        if (board->getPieces()->find(mouse) != board->getPieces()->end()){
            delete board->getPieces()->at(mouse);
            board->getPieces()->erase(mouse);
        }

        (*board->getPieces())[mouse] = board->getSelectedPiece();
        
        board->getPieces()->erase(board->getSelectedPiece()->getPosition());
        board->getSelectedPiece()->setPosition(mouse);
        
        board->setSelectedPiece(nullptr);
        board->setState(SELECT);
    }
}
