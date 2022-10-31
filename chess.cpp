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
    int x = -1;
    int y = 0;
    bool fenTooLong = false;
    for (auto aChar : aStr)
    {/*
        x++;
        if (fenTooLong) continue;
        return;
        switch (aChar)
        {
        case '/':
            x = 0;
            y++;
            if (gameState[x].size() < y) break;

        case 'p':
            gameState[x][y].setPiece(wPawn);
            break;

            //
        }*/
    }
}

bool chess::safetyCheck(int x, int y)
{
    if (x >= gameState.size())
    {
        return false;
    }
    if (y >= gameState[x].size())
    {
        return false;
    }
    return true;
}

void chess::setTileHighlight(int x, int y)
{

}

void chess::pawnMovement(player aColor)
{

}
void chess::knightMovement(player aColor)
{
    int xPlace, yPlace;
    for (int adderIter = -2; adderIter < 4; adderIter += 2)
    {
        for (int singleIter = -1; singleIter < 2; singleIter++)
        {
            xPlace = this->selectedTile->xPos + adderIter;
            yPlace = this->selectedTile->yPos + singleIter;
            if (safetyCheck(xPlace, yPlace))
            {
                setTileHighlight(xPlace, yPlace);
            }
            xPlace = this->selectedTile->xPos + singleIter;
            yPlace = this->selectedTile->yPos + adderIter;
            if (safetyCheck(xPlace, yPlace))
            {
                setTileHighlight(xPlace, yPlace);
            }
        }
    }
    }

void chess::rookMovement(player aColor){}
void chess::bishopMovement(player aColor){}
void chess::queenMovement(player aColor)
{
    rookMovement(aColor);
    bishopMovement(aColor);

}

void chess::kingMovement(player aColor){};
/*
void chess::placePiece(char aChar, int xPos, int yPos)
{
    this->gameState[xPos][yPos]
}*/
