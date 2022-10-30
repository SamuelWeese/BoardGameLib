#include "board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>

#define TESTING_IMAGE_SIZE 1024

board::board( sf::RenderWindow *passWindow, int windowLength, int windowHeight, int boardLength, int boardHeight, int padding)
{
    this->aWindow = passWindow;
    this->height = boardHeight;
    this->length = boardLength;
    this->windowLength = windowLength;
    this->windowHeight = windowHeight;
    auto windowDimension = aWindow->getSize();
    if (!tileTexture.loadFromFile("/tmp/tiletexture.png", sf::IntRect(0, 0, windowDimension.x, windowDimension.y))) // arguments for this are
        //("string name", sf::IntRect(first corner of file (0 for full file), 0 (second corner), size of file, size of file))
    {
        exit(1);
        // error...
    }
    this->padding = padding; // in px
    float scaleX, scaleY;
    scaleX = (this->windowLength - (padding*2))/(float)this->length*( this->tileScaleFloat / (float) windowDimension.x);
    scaleY = (this->windowHeight - (padding*2))/(float)this->height*( this->tileScaleFloat / (float) windowDimension.y);
    for (int x = 0; x < this->length; x++)
    {
        gameState.push_back(std::vector<boardtile>());
        for (int y = 0; y < this->height; y++)
        {
            int positionX, positionY;
            positionX = (this->windowLength -(padding*2)) / boardLength * x + padding;
            positionY = (this->windowHeight -(padding*2)) / boardHeight * y + padding;

            gameState[x].push_back(boardtile(x, y));//, this->tileTexture));
            gameState[x][y].tileSprite.setTexture(this->tileTexture);
            gameState[x][y].tileSprite.setPosition(positionX, positionY);
            gameState[x][y].tileSprite.setScale(scaleX, scaleY);
        }
    }
}

board::~board()
{
    return;
}
int board::getDistanceFromSquare(boardtile &selectedTile, boardtile &anotherTile)
{
    int x = selectedTile.xPos - anotherTile.xPos;
    int y = selectedTile.yPos - anotherTile.yPos;
    return x + y;
}

void board::generateAttackableSquares(boardtile &selectedTile)
{
    for (int x = 0; x < this->length; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            if (this->getDistanceFromSquare(selectedTile, this->gameState[x][y]) <= selectedTile.getMovement())
            {
                if (gameState[x][y].hasUnit())
                {
                    gameState[x][y].setHighlightAttacked();
                }
                else
                {
                    gameState[x][y].setHighlightMoveable();
                }
            }
        }
    }
}

void board::clearBoardHighlights()
{
    for (int x = 0; x < this->length; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            gameState[x][y].setHighlightDefault();
        }
    }
}

void board::draw()
{
    for (int x = 0; x < this->length; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            this->gameState[x][y].draw(aWindow);
        }
    }
}

void board::positionInitial()
{


}
void board::mouseClick(int xPos, int yPos) // this function should maybe return a square or something?
// so that other libs can use it better
{
    this->clearBoardHighlights();
    // finding closest square
    // not sure if I want this to select exact square or just closest
    // exact, click must be within the bounds of a square
    auto windowSize = this->aWindow->getSize();
    int tileLength = ((windowSize.x - this->padding*2) / (this->length));
    int tileHeight = ((windowSize.y - this->padding*2) / (this->height));
    for (int x = 0; x < gameState.size(); x++)
    {
        for (int y = 0; y < gameState[x].size(); y++)
        {
            int tilePosX = ((windowSize.x - this->padding*2) / (this->length)) * x + padding;
            int tilePosY = ((windowSize.y - this->padding*2) / (this->height)) * y + padding;

            if ((xPos - tilePosX) < tileLength && (yPos-tilePosY) < tileHeight
            &&  (xPos - tilePosX) > 0          && (yPos-tilePosY) > 0)
            {
                this->selectedTile = &gameState[x][y];
                gameState[x][y].setHighlightSelected();
                gameState[x][y].clearTile();
                return; // currently all I want the board to do is highlight and select a tile
            }
        }
    }

    /*
    int smallestDistance = INT_MAX;
    distanceToSquare = a*a + b*b
    distanceToSquare = distanceToSquare**/



}


std::string board::generateFEN()
{
    std::string retStr = "";
    unsigned short C; // terrible naming convention for a joke
    for (int x = 0; x < gameState.size(); x++)
    {
        for (int y = 0; y < gameState[x].size(); y++)
        {
            char returnedFEN = gameState[x][y].getFEN();
            if (returnedFEN == ASCII_SPACE_DEFAULT_FEN_CHAR)
            {
                C++; // :)
                continue;
            }
            if (C > 0)
            {
                retStr += std::to_string(C);
                C = 0;
            }
            retStr += gameState[x][y].getFEN();
        }
        retStr += "/";
    }
    return retStr;
}
void keepSquare()
{

}

void squareTiles()
{

}
