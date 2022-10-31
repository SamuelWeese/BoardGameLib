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

    if (!tileTexture.loadFromFile("/tmp/chessTiles.png"))
    {
        throw std::runtime_error("Bad tile sprite texture path.");
    }

    // setting up piece literals
    wPawn.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,1000));
    wRook.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    wKnight.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    wBishop.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    wQueen.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    wKing.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    bPawn.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    bRook.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    bKnight.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    bBishop.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    bQueen.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));
    bKing.setSpriteTextureRect(&chessPieces, sf::IntRect(10,10,100,100));

    this->readFEN(FEN);
    this->setUpInitialBoard();
}

player chess::getPlayer(char aChar)
{
    switch(aChar)
    {
    case 'r':
    case 'n':
    case 'b':
    case 'q':
    case 'k':
    case 'p':
        return black;
    case 'P':
    case 'R':
    case 'N':
    case 'B':
    case 'Q':
    case 'K':
        return white;
    default:
        return none;
    }
}

void chess::readFEN(std::string aStr)
{
    int x = -1;
    int y = 0;
    for (auto aChar : aStr)
    {
        x++;
        if (aChar == '/')
        {
            x = 0;
            y++;
            continue;
        }
        if (!safetyCheck(x, y))
        {
            continue;
        }
        switch (aChar)
        {
        case 'r':
            gameState[x][y].setPiece(bRook);
            break;
        case 'n':
            gameState[x][y].setPiece(bKnight);
            break;
        case 'b':
            gameState[x][y].setPiece(bBishop);
            break;
        case 'q':
            gameState[x][y].setPiece(bQueen);
            break;
        case 'k':
            gameState[x][y].setPiece(bKing);
            break;
        case 'p':
            gameState[x][y].setPiece(bPawn);
            break;
        case 'P':
            gameState[x][y].setPiece(bPawn);
            break;
        case 'R':
            gameState[x][y].setPiece(bPawn);
            break;
        case 'N':
            gameState[x][y].setPiece(bPawn);
            break;
        case 'B':
            gameState[x][y].setPiece(bPawn);
            break;
        case 'Q':
            gameState[x][y].setPiece(bPawn);
            break;
        case 'K':
            gameState[x][y].setPiece(bPawn);
            break;
            // pass
        }
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
    if (!this->gameState[x][y].hasUnit())
    {
        gameState[x][y].setHighlightMoveable();
        return;
    }
    if(getPlayer(this->gameState[x][y].getFEN()) != getPlayer(this->selectedTile->getFEN()))
    {
        gameState[x][y].setHighlightAttackable();
        return;
    }
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
