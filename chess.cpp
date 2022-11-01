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
    wKing = piece('K', &chessPieces, sf::IntRect(25,25,100,100));
    bKing = piece('k', &chessPieces, sf::IntRect(10,180,100,100));

    wPawn = piece('P', &chessPieces, sf::IntRect(1000,25,100,100));
    bPawn = piece('p', &chessPieces, sf::IntRect(1000,180,100,100));

    wRook = piece('R', &chessPieces, sf::IntRect(415,25,100,100));
    bRook = piece('r', &chessPieces, sf::IntRect(415,185,100,100));

    wKnight = piece('N', &chessPieces, sf::IntRect(815,25,100,100));
    bKnight = piece('n', &chessPieces, sf::IntRect(815,180,100,100));

    wBishop = piece('B', &chessPieces, sf::IntRect(615,25,100,100));
    bBishop = piece('b', &chessPieces, sf::IntRect(615,180,100,100));

    wQueen = piece('Q', &chessPieces, sf::IntRect(215,25,100,100));
    bQueen = piece('q', &chessPieces, sf::IntRect(215,185,100,100));


    this->setUpInitialBoard();
    std::string aFEN = "rnbqkbnr/pppppppp/3pnNpPP/3nNP/8/8/PPPPPPPP/RNBQKBNR";
    this->readFEN(aFEN);
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
        if (47 < aChar && aChar < 58)
        {
            x += (aChar - 49);
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
            gameState[x][y].setPiece(wPawn);
            break;
        case 'R':
            gameState[x][y].setPiece(wRook);
            break;
        case 'N':
            gameState[x][y].setPiece(wKnight);
            break;
        case 'B':
            gameState[x][y].setPiece(wBishop);
            break;
        case 'Q':
            gameState[x][y].setPiece(wQueen);
            break;
        case 'K':
            gameState[x][y].setPiece(wKing);
            break;
            // pass default
            // probably should add some way to fix broken FEN, though this does that technically
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

bool chess::setTileHighlight(int x, int y)
{
    if (!this->gameState[x][y].hasUnit())
    {
        gameState[x][y].setHighlightMoveable();
        return false;
    }
    if(getPlayer(this->gameState[x][y].getFEN()) != getPlayer(this->selectedTile->getFEN()))
    {
        gameState[x][y].setHighlightAttackable();
        return true;
    }
    return true;
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
    if (safetyCheck(x,y))
    {
        player tileOwner = getPlayer(this->selectedTile->getFEN());
        player attackedTileOwner = getPlayer(gameState[x][y].getFEN());
        if (tileOwner == none || attackedTileOwner == none) return;
        if (tileOwner != getPlayer(gameState[x][y].getFEN()))
        {
            gameState[x][y].setHighlightAttackable();
        }
    }
}

void chess::pawnMovement()
{
    player pawnOwner = getPlayer(this->selectedTile->getFEN());
    int adder = 1;
    int pawnX = this->selectedTile->xPos;
    int pawnY = this->selectedTile->yPos;
    if (pawnOwner == white){ adder *= -1;}
    else if (pawnOwner == none) { return;}
    int positionY = adder + pawnY;
    int positionX = pawnX;
    setMoveHighlight(positionX, positionY);

    // attack squares!
    for (int i = -1; i < 2; i+=2)
    {
        positionX = pawnX + i;
        setAttackHighlight(positionX, positionY);
    }
    // checking next to back row
    if (pawnOwner == white && gameState[positionX].size() - 2) // signifies not moved
    {
        adder = adder * 2;
        positionY = adder + pawnY;
        setMoveHighlight(pawnX, positionY);
    }
    else if (pawnOwner == black && pawnY == 1) // signifies not moved
    {
        adder = adder * 2;
        positionY = adder + pawnY;
        setMoveHighlight(pawnX, positionY);
    }
}

void chess::knightMovement()
{
    int xPlace, yPlace;
    for (int adderIter = -2; adderIter < 4; adderIter += 4)
    {
        for (int singleIter = -1; singleIter < 2; singleIter += 2)
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
}// FINISHED DON'T TOUCH

void chess::rookMovement()
{
    player rookOwner = getPlayer(this->selectedTile->getFEN());\

    int rookX = this->selectedTile->xPos;
    int rookY = this->selectedTile->yPos;

    for (int i = rookX+1; i < gameState.size(); i++)
    {
        if(!safetyCheck(i,rookY)) break;
        if(setTileHighlight(i, rookY))
        {
            break;
        }
    }
    for (int i = rookX-1; i >= 0; i--)
    {
        if(!safetyCheck(i,rookY)) break;
        if(setTileHighlight(i, rookY))
        {
            break;
        }
    }
    for (int i = rookY+1; i < gameState.size(); i++)
    {
        if(!safetyCheck(rookX,i)) break;
        if(setTileHighlight(rookX, i))
        {
            break;
        }
    }
    for (int i = rookY-1; i >= 0; i--)
    {
        if(!safetyCheck(rookX,i)) break;
        if(setTileHighlight(rookX, i))
        {
            break;
        }
    }
} // FINISHED, DON'T TOUCH
void chess::bishopMovement(){}
void chess::queenMovement()
{
    rookMovement();
    bishopMovement();
}

void chess::kingMovement()
{

}

void chess::mouseChessClick(int a, int b)
{
    clearBoardHighlights();
    mouseClick(a, b);
    char aChar = this->selectedTile->getFEN();
    /* re add for turns
    if (currentPlayerTurn != getPlayer(aChar))
    {
        this->selectedTile->setHighlightSelected();
        return;
    }*/
    switch (aChar)
    {
    case 'b':
    case 'B':
        break;
    case 'p':
    case 'P':
        pawnMovement();
        break;
    case 'n':
    case 'N':
        knightMovement();
        break;
    case 'q':
    case 'Q':
        break;
    case 'k':
    case 'K':
        break;
    case 'r':
    case 'R':
        rookMovement();
        break;
    default:
        this->selectedTile->setHighlightDefault();
    }

}
