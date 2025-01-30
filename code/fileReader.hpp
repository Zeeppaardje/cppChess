

#ifndef FILEREADER
#define FILEREADER

#include "Board.hpp"
#include "Pieces.hpp"
#include "Coordinate.hpp"
#include <iostream>
#include <fstream>
#include <unordered_set>

#include <ctype.h>

Piece* makePiece(char type,Coordinate pos,piece_color color){
    switch (type)
    {
    case 'P':
        return new Pawn(pos,color);
    case 'Q':
        return new Queen(pos,color);
    case 'K':
        return new King(pos,color);
    case 'H':
        return new Knight(pos,color);
    case 'B':
        return new Bishop(pos,color);
    case 'R':
        return new Rook(pos,color);
    default:
        return nullptr;
    }
}


Board* readBoard(std::string file){
    int r;
    std::ifstream in(file);

    if (!in.is_open()){
        std::cerr << "Could'nt read save file";
        return nullptr;
    }
    Board* board = nullptr;
    std::string s;
    int y = 0;
    int bordSize = 0;
    while (getline(in,s))
    {
        if (y == 0){
            bordSize = s[0] - '0'; /* converting the char to int*/
            board = new Board(Coordinate(bordSize,bordSize));
        }
        else{
            char a;
            int x = 0;
            while (x < bordSize){
                a = s[x];
                piece_color color = BLACK;
                if (std::isupper(a)){
                    color = WHITE;
                }
                a = std::toupper(a);
                Piece* newPiece = makePiece(a,Coordinate(x,bordSize - y),color);
                board->addPiece(newPiece);
                x++;
            }
        }
        y++;
    }   
    in.close();
    return board;
}


#endif