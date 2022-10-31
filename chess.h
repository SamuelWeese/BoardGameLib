#ifndef CHESS_H
#define CHESS_H
#include "board.h"

#define CHESS_LENGTH 8

enum player { black, white, none};

class chess : public board
{
    sf::Texture chessPieces;
    // below should probably be some form of const static for vanilla chess, but these pieces are extendable
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

    player getPlayer(char aChar);

    //
    bool safetyCheck(int x, int y);
    void setTileHighlight(int x, int y);
    // functors
    void pawnMovement(player aColor);
    void knightMovement(player aColor);

    void rookMovement(player aColor);
    void bishopMovement(player aColor);
    void queenMovement(player aColor);

    void kingMovement(player aColor);

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
