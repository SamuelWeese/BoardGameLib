#ifndef CHESS_H
#define CHESS_H
#include "board.h"

#define CHESS_LENGTH 12

class chess : public board
{
    sf::Texture chessPieces;
    sf::Texture chessTiles;
    // below should probably be some form of const static for vanilla chess
    piece wPawn;
    piece wRook;
    piece wKnight;
    piece wBishop;
    piece wQueen;
    piece wKing;
    piece bPawn;
    piece bRook;
    piece bKnight;
    piece bBishop;
    piece bQueen;
    piece bKing;
public:
    explicit chess(sf::RenderWindow *aWindow, std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    // virtual overrides
    void readFEN(std::string) override;
};

#endif // CHESS_H
/*
 *     sf::Texture whitePawn;
    chess aBoard(&window);
    piece aPiece(&whitePawn);
    aPiece.setSpriteTexture(&whitePawn);
    for (int x = 0; x < aBoard.gameState.size(); x++)
    {
        for (int y = 0; y < aBoard.gameState[x].size(); y++)
        {
            aBoard.gameState[x][y].setPiece(aPiece);
        }
    }
    if (!whitePawn.loadFromFile("/tmp/chess.png", sf::IntRect(0, 0, 100, 100))) // arguments for this are
        //("string name", sf::IntRect(first corner of file (0 for full file), 0 (second corner), size of file, size of file))
    {
        exit(1);
        // error...
    }*/
