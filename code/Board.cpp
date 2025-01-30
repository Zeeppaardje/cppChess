#include "Board.h"
#include <unordered_map>
#include "Pieces.h"
#include "Coordinate.h"
#include "hashFunctions.h"
#include "types.h"
#include "ActionHandler.h"

Board::Board(Coordinate bounds)
{
    this->bounds = bounds;
    this->pieces = new std::unordered_map<Coordinate,Piece*,HashFunction>;
    this->selectedPiece = NULL;
    this->playerAmount = 2;
    this->turn = 0;
    this->state = SELECT;
    this->actions = new std::unordered_map<actionState,ActionHandler*>{
        {SELECT,new SelectActionHandler()},
        {PLAY,new PlayActionHandler()}
        };  
}

Board::~Board()
{
    for (auto it = this->pieces->begin(); it != this->pieces->end(); it++)
    {
        std::cout << "deleting " << it->second->getPosition() << std::endl;
        delete it->second;
    }
    for (auto it = this->actions->begin(); it != this->actions->end(); it++){
        delete it->second;
    }
    delete this->actions;
    delete pieces;
}
void Board::nextPlayer()
{
    this->turn = (this->turn + 1) % this->playerAmount;
}

void Board::action(Coordinate mouse)
{
    this->actions->at(this->state)->onClick(mouse,this);

}

std::unordered_map<Coordinate, Piece *, HashFunction> *Board::getPieces() const
{
    return this->pieces;
}

void Board::addPiece(Piece* piece)
{
    if (!piece){
        return;
    }
    (*this->pieces)[piece->getPosition()] = piece;
    piece->setBound(this->bounds);
    piece->setBoard(this);
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

int Board::getTurn() const
{
    return this->turn;
}

void Board::setTurn(int t)
{
    this->turn = t;
}

Piece *Board::getSelectedPiece()
{
    return this->selectedPiece;
}

void Board::setSelectedPiece(Piece *p)
{
    this->selectedPiece = p;
}

actionState Board::getState() const
{
    return this->state;
}

void Board::setState(actionState state)
{
    this->state = state;
}
