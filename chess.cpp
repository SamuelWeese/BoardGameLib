#include "chess.h"

chess::chess(sf::RenderWindow *aWindow, std::string FEN) : board(aWindow)
{
    this->length = CHESS_LENGTH;
    this->height = CHESS_LENGTH;

    // setting up textures
    if (!chessPieces.loadFromFile("/tmp/chessPieces.png"))
    {
         throw std::runtime_error("Bad piece sprite texture path.");
    }

    if (!chessTiles.loadFromFile("/tmp/chessTiles.png"))
    {
        throw std::runtime_error("Bad tile sprite texture path.");
    }

    // setting up piece literals
    wPawn.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    wRook.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    wKnight;
    wBishop;
    wQueen;
    wKing;
    bPawn;
    bRook;
    bKnight;
    bBishop;
    bQueen;
    bKing;

    this->readFEN(FEN);
    this->setUpInitialBoard();
}

void chess::readFEN(std::string aStr)
{
    int x = 0;
    int y = 0;
    bool fenTooLong = false;
    for (auto aChar : aStr)
    {
        // TODO
        if (fenTooLong) continue;
        switch (aChar)
        {
        case '/':
            x = 0;
            y++;
            if (gameState[x].size() < y)
            break;
        case 'p':
            gameState[x][y].setPiece(wPawn);

            //
        }
    }
}
/*
void chess::placePiece(char aChar, int xPos, int yPos)
{
    this->gameState[xPos][yPos]
}*/
