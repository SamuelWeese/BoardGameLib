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
    wPawn = piece('P', &chessPieces, sf::IntRect(0,0,10,10));
    wRook = piece('R', &chessPieces, sf::IntRect(0,0,1024,1024));
    wKnight = piece('N', &chessPieces, sf::IntRect(0,0,1024,1024));
    wBishop = piece('B', &chessPieces, sf::IntRect(0,0,1024,1024));
    wQueen = piece('Q', &chessPieces, sf::IntRect(217,126,125,125));
    wKing = piece('K', &chessPieces, sf::IntRect(25,25,125,125));
    bPawn = piece('p', &chessPieces, sf::IntRect(20,24,100,100));
    bRook = piece('r', &chessPieces, sf::IntRect(0,0,1024,1024));
    bKnight = piece('n', &chessPieces, sf::IntRect(0,0,1024,1024));
    bBishop = piece('b', &chessPieces, sf::IntRect(0,0,1024,1024));
    bQueen = piece('q', &chessPieces, sf::IntRect(217,126,125,125));
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
    int x = 0;
    int y = 0;
    for (auto aChar : aStr)
    {
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
            gameState[x][y].setPiece(wPawn);
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
        x++;
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

void chess::setMoveHighlight(int x, int y)
{
    if (safetyCheck(x,y))
    {
        if (!gameState[x][y].hasUnit())
        {
            gameState[x][y].setHighlightMoveable();
        }
    }
}
void chess::setAttackHighlight(int x, int y)
{
    player tileOwner = getPlayer(this->selectedTile->getFEN());
    if (tileOwner == none) return;
    if (safetyCheck(x,y))
    {
        if (tileOwner != getPlayer(gameState[x][y].getFEN()))
        {
            gameState[x][y].setHighlightAttackable();
        }
    }
}

void chess::pawnMovement(player aColor)
{
    player pawnOwner = getPlayer(this->selectedTile->getFEN());
    int adder = 1;
    int pawnX = this->selectedTile->xPos;
    int pawnY = this->selectedTile->yPos;
    if (pawnOwner == black){ adder *= 1;}
    else if (pawnOwner == none) { return;}
    int positionY = adder + pawnY;
    int positionX = pawnX;
    setMoveHighlight(positionX, positionY);

    // checking next to back row
    if (pawnOwner == white && pawnY == 1) // signifies not moved
    {
        adder = adder * 2;
        setMoveHighlight(positionX, positionY);
    }
    if (pawnOwner == black && pawnY == gameState[positionX].size() - 2) // signifies not moved
    {
        adder = adder * 2;
        setMoveHighlight(positionX, positionY);
    }
    // attack squares!
    for (int i = -1; i < 2; i+=2)
    {
        positionX = adder + i;
        setAttackHighlight(positionX, positionY);
    }
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

void chess::kingMovement(player aColor)
{

};
/*
void chess::placePiece(char aChar, int xPos, int yPos)
{
    this->gameState[xPos][yPos]
}*/
