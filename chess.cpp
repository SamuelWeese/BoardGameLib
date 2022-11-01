#include "chess.h"

chess::chess(sf::RenderWindow *aWindow, std::string FEN) : board(aWindow)
{
    this->length = CHESS_LENGTH;
    this->height = CHESS_LENGTH;

    // setting up textures
    if (!chessPieces.loadFromFile("/tmp/tiletexture.png"))
    {
         throw std::runtime_error("Bad piece sprite texture path.");
    }

    if (!tileTexture.loadFromFile("/tmp/chessTiles.png"))
    {
        throw std::runtime_error("Bad tile sprite texture path.");
    }

    // setting up piece literals
    wPawn = piece('P', &chessPieces, sf::IntRect(0,0,1024,1024));
    wRook = piece('R', &chessPieces, sf::IntRect(0,0,1024,1024));
    wKnight = piece('N', &chessPieces, sf::IntRect(0,0,1024,1024));
    wBishop = piece('B', &chessPieces, sf::IntRect(0,0,1024,1024));
    wQueen = piece('Q', &chessPieces, sf::IntRect(0,0,1024,1024));
    wKing = piece('K', &chessPieces, sf::IntRect(0,0,1024,1024));
    bPawn = piece('p', &chessPieces, sf::IntRect(0,0,1024,1024));
    bRook = piece('r', &chessPieces, sf::IntRect(0,0,1024,1024));
    bKnight = piece('n', &chessPieces, sf::IntRect(0,0,1024,1024));
    bBishop = piece('b', &chessPieces, sf::IntRect(0,0,1024,1024));
    bQueen = piece('q', &chessPieces, sf::IntRect(0,0,1024,1024));
    bKing = piece('k', &chessPieces, sf::IntRect(0,0,1024,1024));

    this->setUpInitialBoard();
    this->readFEN(FEN);
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
