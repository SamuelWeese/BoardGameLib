#ifndef CHESS_H
#define CHESS_H
#include "board.h"

#define CHESS_LENGTH 8

enum player { white, black, none}; // none should always be last

class chess : public board
{
    player currentPlayerTurn;
    bool aiEnabled;
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

    boardtile *oldSelection;

    player getPlayer(char aChar);
    void iteratePlayer();

    //
    bool safetyCheck(int x, int y);

    // functors
    void pawnMovement();
    void knightMovement();
    void rookMovement();
    void bishopMovement();
    void queenMovement();
    void kingMovement();

    bool setHighlightFlag(int x, int y, bool flagStatus = true);
    void clearBoardHighlightFlag();
    bool checkLegality(std::string gamePosition = ""); // [this](){this->generateFEN();} works dependent on cpp version (c11)
    bool checkLegalityAlgebraic(std::string aMove);

public:
    chess(sf::RenderWindow *aWindow, std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    bool setTileHighlight(int x, int y);
    bool setMoveHighlight(int x, int y);
    void setAttackHighlight(int x, int y);
    void mouseChessClick(int a, int b);



    // virtual overrides
    void readFEN(std::string) override;
};

#endif // CHESS_H
