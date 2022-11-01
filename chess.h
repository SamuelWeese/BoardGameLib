#ifndef CHESS_H
#define CHESS_H
#include "board.h"

#define CHESS_LENGTH 8

enum player { black, white, none};

class chess : public board
{
    player currentPlayerTurn;
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
    // functors
    void pawnMovement();
    void knightMovement();
    void rookMovement();
    void bishopMovement();
    void queenMovement();
    void kingMovement();

public:
    explicit chess(sf::RenderWindow *aWindow, std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    bool setTileHighlight(int x, int y);
    void setMoveHighlight(int x, int y);
    void setAttackHighlight(int x, int y);
    void mouseChessClick(int a, int b);


    // virtual overrides
    void readFEN(std::string) override;
};

#endif // CHESS_H
