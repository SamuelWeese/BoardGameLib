﻿#include "chess.h"

chess::chess(sf::RenderWindow *aWindow, std::string FEN) : board(aWindow)
{
    this->length = CHESS_LENGTH;
    this->height = CHESS_LENGTH;
    this->currentPlayerTurn = static_cast<player>(0);

    // setting up textures
    if (!chessPieces.loadFromFile("/tmp/chessPieces.png"))
    {
         throw std::runtime_error("Bad piece sprite texture path.");
    }

    if (!tileTexture.loadFromFile("/tmp/chessTiles.png"))
    {
        throw std::runtime_error("Bad tile sprite texture path.");
    }
    sf::IntRect lightSquareRect(200, 200, 20, 20);
    sf::IntRect darkSquareRect(100, 100, 20, 20);


    // setting up piece literals
    wKing = piece('K', &chessPieces, sf::IntRect(15,25,100,100));
    bKing = piece('k', &chessPieces, sf::IntRect(15,180,100,100));

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

    auto windowDimension =  aWindow->getSize();
    int scaleX, scaleY; // windowSize - padding * 2 is to ensure tile only in the "play space"
    // divided by number of tile, then multiplied by th
    scaleX = (windowDimension.x - (padding*2))/(float)this->length - padding/10;
    scaleY = (windowDimension.y - (padding*2))/(float)this->height - padding/10;
    // TODO move all below into a boardtile function for changeing texture
    // this should be implicit, just code could get funky
    for (int x = 0; x < this->length; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            // below highlights issues with the default set up
            // possible solution is allowing functors for default set up?
            if (x%2 + y%2 == 1)
            {
                gameState[x][y].setTextureByRect(darkSquareRect);
            }
            else
            {
                gameState[x][y].setTextureByRect(lightSquareRect);
            }
            gameState[x][y].scaleTile(scaleX, scaleY);
            if (gameState[x][y].flags.size() != 0)
            {
                throw std::runtime_error("Flags already exist! Cannot force unhighlighted flag!");
            }
            bool isHighlighted = false;
            gameState[x][y].flags.push_back(isHighlighted); // this is constructor needed for setHighlightFlag()
        }
    }
    std::string aFEN = "/ppP/3pnNpPP/3nNP/bB3bB/21Qq/pPp3PP/k6K"; // TODO remove later
    this->readFEN(aFEN);
    this->currentFEN = generateFEN();
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

void chess::iteratePlayer()
{
    this->currentPlayerTurn = static_cast<player>(static_cast<int>(this->currentPlayerTurn) + 1);
    if (this->currentPlayerTurn == none)
    {
        this->currentPlayerTurn = static_cast<player>(0);
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
    if (x >= gameState.size() || x < 0)
    {
        return false;
    }
    if (y >= gameState[x].size() || y < 0)
    {
        return false;
    }
    return true;
}

bool chess::checkLegality(std::string gamePosition)
{
    std::cout << gamePosition << std::endl;
    if (gamePosition.length() == 0) gamePosition = this->generateFEN();
    std::cout << "Final Position:" << gamePosition << std::endl;
    char boardState[CHESS_LENGTH][CHESS_LENGTH] = { ASCII_SPACE_DEFAULT_FEN_CHAR };
    int x = 0;
    int y = 0;
    for (int i = 0; i < gamePosition.length(); i++)
    {
        char aChar = gamePosition[i];
        if (aChar == '/')
        {
            x = 0;
            y++;
            continue;
        }
        if (!safetyCheck(x, y))
        {
            return false;
        }
        if (47 < aChar && aChar < 58)
        {
            x += (aChar - 49);
            continue;
        }
        boardState[x][y] = aChar;
    }
    // TODO seperate below into C lib
    char kingChar, pawnChar, rookChar, knightChar, bishopChar, queenChar;
    int pawnAdder;
    switch (this->currentPlayerTurn)
    {
    case white:
        kingChar = 'K';
        pawnChar = 'p';
        rookChar = 'r';
        knightChar = 'n';
        bishopChar = 'b';
        queenChar = 'q';
        pawnAdder = -1;
        break;
    case black:
        kingChar = 'k';
        pawnChar = 'P';
        rookChar = 'R';
        knightChar = 'N';
        bishopChar = 'B';
        queenChar = 'Q';
        pawnAdder = 1;
        break;
    }

    for (x = 0; x < CHESS_LENGTH; x++)
    {
        for (y = 0; y < CHESS_LENGTH; y++)
        {
            if (boardState[x][y] == kingChar)
            {
                std::cout << boardState[x][y];
                // TODO change safety check to new lib specific function, char array not vector
                int xPlace, yPlace;

                // PAWN CHECKING
                yPlace = y+pawnAdder;
                for(int i = -1; i <= 1; i+=2)
                {
                    xPlace = x+i;
                    if (safetyCheck(xPlace, yPlace))
                    {
                        if (boardState[xPlace][yPlace] == pawnChar) return false;
                    }
                }

                // KNIGHT CHECKING
                xPlace = x;
                yPlace = y;
                for (int adderIter = -2; adderIter < 4; adderIter += 4)
                {
                    for (int singleIter = -1; singleIter < 2; singleIter += 2)
                    {
                        xPlace = x + adderIter;
                        yPlace = y + singleIter;
                        if (safetyCheck(xPlace, yPlace))
                        {
                            if (boardState[x][y] == knightChar) return false;
                        }
                        xPlace = x + singleIter;
                        yPlace = y+ adderIter;
                        if (safetyCheck(xPlace, yPlace))
                        {
                            if (boardState[xPlace][yPlace] == knightChar) return false;
                        }
                    }
                }

                // ROOK and QUEEN CHECKING
                xPlace = x;
                yPlace = y;
                for (int i = xPlace+1; i < CHESS_LENGTH; i++)
                {
                    if(!safetyCheck(i,yPlace)) break;
                    if (boardState[i][yPlace] == rookChar) return false;
                    if (boardState[i][yPlace] == queenChar) return false;
                    if (boardState[i][yPlace] != ASCII_SPACE_DEFAULT_FEN_CHAR) break;
                }
                for (int i = xPlace-1; i >= 0; i--)
                {
                    if(!safetyCheck(i,yPlace)) break;
                    if (boardState[i][yPlace] == rookChar) return false;
                    if (boardState[i][yPlace] == queenChar) return false;
                    if (boardState[i][yPlace] != ASCII_SPACE_DEFAULT_FEN_CHAR) break;
                }
                for (int i = yPlace+1; i < CHESS_LENGTH; i++)
                {
                    if(!safetyCheck(xPlace,i)) break;
                    if (boardState[xPlace][i] == rookChar) return false;
                    if (boardState[xPlace][i] == queenChar) return false;
                    if (boardState[xPlace][i] != ASCII_SPACE_DEFAULT_FEN_CHAR) break;
                }
                for (int i = xPlace-1; i >= 0; i--)
                {
                    if(!safetyCheck(xPlace,i)) break;
                    if (boardState[xPlace][i] == rookChar) return false;
                    if (boardState[xPlace][i] == queenChar) return false;
                    if (boardState[xPlace][i] != ASCII_SPACE_DEFAULT_FEN_CHAR) break;
                }


                // BISHOP CHECK

                for (int i = 1; (i+x) < CHESS_LENGTH && (i+y) < CHESS_LENGTH; i++)
                {
                    xPlace = x + i;
                    yPlace = y + i;
                    if(!safetyCheck(xPlace, yPlace)) break;
                    if (boardState[xPlace][yPlace] == bishopChar) return false;
                    if (boardState[xPlace][yPlace] == queenChar) return false;
                    if (boardState[xPlace][yPlace] != ASCII_SPACE_DEFAULT_FEN_CHAR) break;
                }
                for (int i = 1; (x + i) < CHESS_LENGTH && (y - i) >= 0; i++)
                {
                    xPlace = x + i;
                    yPlace = y - i;
                    if(!safetyCheck(xPlace, yPlace)) break;
                    if (boardState[xPlace][yPlace] == bishopChar) return false;
                    if (boardState[xPlace][yPlace] == queenChar) return false;
                    if (boardState[xPlace][yPlace] != ASCII_SPACE_DEFAULT_FEN_CHAR) break;
                }
                for (int i = 1; (x - i) >= 0 && (i+y) < CHESS_LENGTH; i++)
                {
                    xPlace = x - i;
                    yPlace = y + i;
                    if(!safetyCheck(xPlace, yPlace)) break;
                    if (boardState[xPlace][yPlace] == bishopChar) return false;
                    if (boardState[xPlace][yPlace] == queenChar) return false;
                    if (boardState[xPlace][yPlace] != ASCII_SPACE_DEFAULT_FEN_CHAR) break;
                }
                for (int i = 1; (x - i) >= 0 && (y - i) >= 0; i++)
                {
                    xPlace = x - i;
                    yPlace = y - i;
                    if(!safetyCheck(xPlace, yPlace)) break;
                    if (boardState[xPlace][yPlace] == bishopChar) return false;
                    if (boardState[xPlace][yPlace] == queenChar) return false;
                    if (boardState[xPlace][yPlace] != ASCII_SPACE_DEFAULT_FEN_CHAR) break;
                }
            }
        }
    }

    return true;

}

bool chess::checkLegalityAlgebraic(std::string aMove)
{
    return false;
}

std::string chess::onlyFENMove(int x1, int y1, int x2, int y2, std::string aStr)
{
    if (aStr.length() == 0) aStr = generateFEN();
    char movingPiece = ASCII_SPACE_DEFAULT_FEN_CHAR;
    int x = 0;
    int y = 0;
    int iteratorTracker = 0;
    for (int i = 0; i < aStr.length(); i++)
    {
        if (aStr[i] == '/')
        {
            x = 0;
            y++;
            continue;
        }
        // removed safety check here, this could cause some real issues TODO
        if (47 < aStr[i] && aStr[i] < 58)
        {
            x += (aStr[i] - 49);
            continue;
        }
        if (x == x1 && y == y1)
        {
            movingPiece = aStr[i];
            aStr[i] = ASCII_SPACE_DEFAULT_FEN_CHAR;
        }
        if (x == x2 && y == y2)
        {
            iteratorTracker = i;
        }
        x++;
    }
    aStr[iteratorTracker] = movingPiece;
    std::cout << "onlyFEN move: "<< aStr << std::endl;
    return aStr;
}

bool chess::setTileHighlight(int x, int y)
{
    if (safetyCheck(x, y))
    {
        if (!this->gameState[x][y].hasUnit())
        {
            gameState[x][y].setHighlightMoveable();
            setHighlightFlag(x, y);
            return false;
        }
        if(getPlayer(this->gameState[x][y].getFEN()) != getPlayer(this->selectedTile->getFEN()))
        {
            gameState[x][y].setHighlightAttackable();
            setHighlightFlag(x, y);
            return true;
        }
    }
    return true;
}

bool chess::setMoveHighlight(int x, int y)
{
    if (safetyCheck(x,y))
    {
        if (!gameState[x][y].hasUnit())
        {
            gameState[x][y].setHighlightMoveable();
            setHighlightFlag(x, y);
            return true;
        }
    }
    return false;
}

void chess::setAttackHighlight(int x, int y) // not bool because only pawn uses
{
    if (safetyCheck(x,y))
    {
        player tileOwner = getPlayer(this->selectedTile->getFEN());
        player attackedTileOwner = getPlayer(gameState[x][y].getFEN());
        if (tileOwner == none || attackedTileOwner == none) return;
        if (tileOwner != getPlayer(gameState[x][y].getFEN()))
        {
            gameState[x][y].setHighlightAttackable();
            setHighlightFlag(x, y);
        }
    }
}

bool chess::setHighlightFlag(int x, int y, bool flagStatus)
{
    if (safetyCheck(x, y)) // this may seem redundant, but check is optimized out with 1 and higher
    {
        if (gameState[x][y].flags.size() >= 1)
        {
            gameState[x][y].flags[0] = flagStatus;
            return true;
        }
    }
    throw std::runtime_error("Highlight flag unable to set!");
    return false;
}

void chess::clearBoardHighlightFlag()
{
    for (int x = 0; x < this->length; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            setHighlightFlag(x, y, false);
        }
    }
}

void chess::pawnMovement()
{
    std::string legalityStr;
    player pawnOwner = getPlayer(this->selectedTile->getFEN());
    int adder = 1;
    int pawnX = this->selectedTile->xPos;
    int pawnY = this->selectedTile->yPos;
    if (pawnOwner == white){ adder *= -1;}
    else if (pawnOwner == none) { return;}
    int positionY = adder + pawnY;
    int positionX = pawnX;
    bool movable = setMoveHighlight(positionX, positionY);
    // attack squares!
    for (int i = -1; i < 2; i+=2)
    {
        positionX = pawnX + i;
        legalityStr = this->currentFEN;
        if (checkLegality(onlyFENMove(pawnX, pawnY, positionX, positionY)))
        {
            setAttackHighlight(positionX, positionY);
        }
    }
    // checking next to back row
    if (!movable) {return;}
    if (pawnOwner == white && pawnY == gameState[positionX].size() - 2) // signifies not moved
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
} // TODO add queening/piece selections

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
void chess::bishopMovement()
{
    int bishopX = this->selectedTile->xPos;
    int bishopY = this->selectedTile->yPos;
    int xTile, yTile;

    for (int i = 1; (i+bishopX) < gameState.size() && (i+bishopY) < gameState[i+bishopX].size(); i++)
    {
        xTile = bishopX + i;
        yTile = bishopY + i;
        if(!safetyCheck(xTile, yTile)) break;
        if(setTileHighlight(xTile, yTile))break;
    }
    for (int i = 1; (bishopX + i) < gameState.size() && (bishopY - i) >= 0; i++)
    {
        xTile = bishopX + i;
        yTile = bishopY - i;
        if(!safetyCheck(xTile, yTile)) break;
        if(setTileHighlight(xTile, yTile))break;
    }
    for (int i = 1; (bishopX - i) >= 0 && (i+bishopY) < gameState[bishopX + i].size(); i++)
    {
        xTile = bishopX - i;
        yTile = bishopY + i;
        if(!safetyCheck(xTile, yTile)) break;
        if(setTileHighlight(xTile, yTile))break;
    }
    for (int i = 1; (bishopX - i) >= 0 && (bishopY - i) >= 0; i++)
    {
        xTile = bishopX - i;
        yTile = bishopY - i;
        if(!safetyCheck(xTile, yTile)) break;
        if(setTileHighlight(xTile, yTile))break;
    }
} // DONE, needs more testing TODO
void chess::queenMovement()
{
    rookMovement();
    bishopMovement();
}

void chess::kingMovement()
{
    int kingX = this->selectedTile->xPos;
    int kingY = this->selectedTile->yPos;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (checkLegality(onlyFENMove(kingX, kingY, kingX + i, kingY + j)))
            {
                setTileHighlight(kingX + i, kingY + j);
            }
        }
    }
}

void chess::mouseChessClick(int a, int b)
{
    // design wise not sure how much should be incorporated to board
    // I should probably redesign this later TODO
    this->oldSelection = selectedTile;
    mouseClick(a, b);
    if (oldSelection == selectedTile) return;
    clearBoardHighlights();
    if (this->selectedTile->flags[0] == true && this->selectedTile != nullptr)
    {
        movePiece(oldSelection->xPos, oldSelection->yPos, this->selectedTile->xPos, this->selectedTile->yPos);
        this->iteratePlayer();
        this->clearBoardHighlightFlag();
        this->selectedTile = nullptr;
        this->oldSelection = nullptr;
        this->currentFEN = generateFEN();
        return;
    }
    char aChar = this->selectedTile->getFEN();
    this->clearBoardHighlightFlag();
    this->selectedTile->setHighlightSelected();
    if (currentPlayerTurn != getPlayer(aChar))
    {
        this->selectedTile->setHighlightSelected();
        return;
    }
    switch (aChar)
    {
    case 'b':
    case 'B':
        bishopMovement();
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
        queenMovement();
        break;
    case 'k':
    case 'K':
        kingMovement();
        break;
    case 'r':
    case 'R':
        rookMovement();
        break;
    default:
        this->selectedTile->setHighlightDefault();
    }
}




