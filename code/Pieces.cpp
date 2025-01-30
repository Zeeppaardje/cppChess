#include "Pieces.hpp"
#include "Coordinate.hpp"
#include "types.hpp"
#include <vector>
#include <unordered_set>


Piece::Piece(Coordinate position, piece_color color) : position(position), color(color), move_count(0) {}

Piece::~Piece(){}

void Piece::add_move_count()
{
    move_count++;
}

Coordinate Piece::getPosition() const
{
    return this->position;
}

piece_color Piece::getColor() const
{
    return color;
}

std::string Piece::getImagePath() const
{
    static std::string enumToString[2] = {"white","black"};
    return "sprites/" + enumToString[color] + '-' + name + ".png";
}

void Piece::setPosition(const Coordinate & position)
{
    this->position = position;
}

void Piece::setBound(Coordinate bounds)
{
    this->bounds = bounds;
}

void Piece::setBoard(Board *board)
{
    this->board = board;
}

Board* Piece:: getBoard() const{
    return board;
}



bool validCoordinate(Board* board,Coordinate coord,piece_color c){
    /* position out of board*/
    if (coord.x >= board->bounds.x || coord.x < 0 || coord.y >= board->bounds.y || coord.y < 0){
        return false;
    }

    /*place taken bij piece of same color*/
    if (board->getPieces()->find(coord) != board->getPieces()->end() && board->getPieces()->at(coord)->getColor() == c){
        return false;
    }
    return true;
}

// PAWN

Pawn::Pawn(Coordinate pos, piece_color color) : Piece(pos,color)
{
    name = "pawn";
}

std::unordered_set<Coordinate,HashFunction> Pawn::possible_moves()
{

    static std::vector<Coordinate> color_direction = {Coordinate(0,1),Coordinate(0,-1)};

    std::unordered_set<Coordinate,HashFunction> moves;
    int steps = 1;

    if (move_count == 0){
        steps = 2;
    }
    for (int i = 1; i <= steps; i ++){
        int y = position.y + i * color_direction[color].y;
        Coordinate newCoord(position.x,y);
        if (validCoordinate(board,newCoord,color) && (board->getPieces()->find(newCoord) == board->getPieces()->end())){
            moves.insert(newCoord);
        }
    }
    /* find attackable pieces*/
    for (int i = -1; i < 2; i += 2) {
        Coordinate check = position + Coordinate(i,0) + color_direction[color];
        if (validCoordinate(board,check,color) && (board->getPieces()->find(check) != board->getPieces()->end())){
            moves.insert(check);
        }
    }
    return moves;
}

/*KING*/


/* beter maken met bv, elke piece een eigen attack veld zonder pieces die in de weg zitten, vermijd infinite king loop en king pakt stukken op gevaarlijke plek*/
bool safeCoordinate(Board* board,Coordinate coord, piece_color color){

    for (auto piece = board->getPieces()->begin();piece != board->getPieces()->end();++piece){
        if (piece->second->name != "king" && piece->second->getColor() != color && piece->second->possible_moves().find(coord) != piece->second->possible_moves().end()){
            return false;
        }
    }
    return true;
}

King::King(Coordinate pos, piece_color color) : Piece(pos,color)
{   
    name = "king"; 
}
std::unordered_set<Coordinate, HashFunction> King::possible_moves()
{   

    std::unordered_set<Coordinate,HashFunction> moves;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {

            Coordinate newCoord = position + Coordinate(i,j);
            if (validCoordinate(board,newCoord,color) && safeCoordinate(board,newCoord,color)){
                moves.insert(newCoord);
            }
        }
        
    }
    return moves;
}

std::unordered_set<Coordinate, HashFunction> movesDirection(Coordinate start,Coordinate direction,piece_color color,Board* board){
    std::unordered_set<Coordinate, HashFunction> moves;
    int steps = 1;
    while (validCoordinate(board,start + steps * direction,color)){
        moves.insert(start + steps * direction);
        if (board->getPieces()->find(start + steps * direction) != board->getPieces()->end() && board->getPieces()->at(start + steps * direction)->getColor() != color)
            break;
        steps += 1;
    }
    return moves;
}

Queen::Queen(Coordinate pos, piece_color color) : Piece(pos,color)
{
    name = "queen";
}

std::unordered_set<Coordinate, HashFunction> Queen::possible_moves()
{
    std::unordered_set<Coordinate, HashFunction> moves;

    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j ++){
            if (i != 0 || j != 0)
                moves.merge(movesDirection(position,Coordinate(i,j),color,board));
        }
    }
    return moves;
}

Rook::Rook(Coordinate pos, piece_color color) : Piece(pos,color)
{
    name = "rook";
}

std::unordered_set<Coordinate, HashFunction> Rook::possible_moves()
{
    std::unordered_set<Coordinate, HashFunction> moves;

    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j ++){
            if ((i == 0) != (j == 0))
                moves.merge(movesDirection(position,Coordinate(i,j),color,board));
        }
    }
    return moves;
}

Bishop::Bishop(Coordinate pos, piece_color color) : Piece(pos,color)
{
    name = "bishop";
}

std::unordered_set<Coordinate, HashFunction> Bishop::possible_moves()
{
    std::unordered_set<Coordinate, HashFunction> moves;

    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j ++){
            if (i != 0 && j != 0)
                moves.merge(movesDirection(position,Coordinate(i,j),color,board));
        }
    }
    return moves;
}

Knight::Knight(Coordinate pos, piece_color color) : Piece(pos,color)
{
    name = "knight";
}

std::unordered_set<Coordinate, HashFunction> Knight::possible_moves()
{
    std::unordered_set<Coordinate,HashFunction> moves;

    for (size_t x = 1; x <= 2; x++)
    {
        for (size_t y = 1; y <= 2; y++)
        {
            if (x != y)
                for (int i = -1; i < 2; i += 2){
                    for (int j = -1; j < 2; j += 2){
                        Coordinate newCoord(position.x + i * x,position.y + j * y);
                        if (validCoordinate(board,newCoord,color)){
                            moves.insert(newCoord);
                        }
                    }
            }
        }
        
    }
    
    return moves;
}
