#include "minesweeper.h"
#include <cassert>
#include <random>
#include <cstring>
#include <SFML/Graphics.hpp>

// TODO
/* Add safe loop using custom iterators
 * Add feeding to video
 *
 *
 *
 *
 *
 * */

bool safetyCheck(long value, long min, long max)
{
    if (value >= max) return false;
    if (value < min) return false;
    return true;
}

minesweeper::minesweeper(sf::RenderWindow *aWindow, u_int size, u_int bombs)
{
    this->playing = true;
    this->size = size;
    this->bombs = bombs;
    if (size*size < bombs)
        this->bombs = size * size;

    this->padding = 0;
    this->boardState = std::vector<std::vector<u_int>>(size, std::vector<u_int>(size, 0));

    this->boardVisible = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
    srand(999);


    this->window = aWindow;

    if (!spriteSheet.loadFromFile("/tmp/sprite_sheet.png"))
    {
        throw std::runtime_error("Bad tile sprite texture path.");
    }
    auto windowDimension = window->getSize();
    float scaleX, scaleY; // windowSize - padding * 2 is to ensure tile only in the "play space"
    scaleX = (float)windowDimension.x/(float)(10*size) - padding*2;
    scaleY = (float)windowDimension.y/(float)(10*size) - padding*2;
    int positionX, positionY;
    for (u_int x_iter = 0; x_iter < size; x_iter++)
    {
        this->spriteVector.push_back(std::vector<sf::Sprite>() );
        for (u_int y_iter = 0; y_iter < size; y_iter++)
        {
            this->spriteVector[x_iter].push_back(sf::Sprite());
            positionX = (windowDimension.x -(padding*2)) / size * x_iter + padding;
            positionY = (windowDimension.y -(padding*2)) / size * y_iter + padding;

            spriteVector[x_iter][y_iter].setPosition(positionX, positionY);
            spriteVector[x_iter][y_iter].scale(scaleX, scaleY);
            spriteVector[x_iter][y_iter].setTexture(this->spriteSheet);
            spriteVector[x_iter][y_iter].setTextureRect(sf::IntRect(20,0,30,10));

        }
    }


}

minesweeper::~minesweeper()
{
}

void minesweeper::createRBoard()
{
    this->seedRBoard();
    this->numberBoard();
}

void minesweeper::seedRBoard()
{
    u_int x, y;
    u_int currentBombs = 0;
    while (currentBombs < bombs)
    {
        x = rand()%(size);
        y = rand()%(size);
        if (this->boardState[x][y] == bomb)
            continue;
        this->boardState[x][y] = bomb;
        currentBombs++;

    }
}

void minesweeper::numberBoard()
{
    u_int index_X, index_Y;
    for (u_int x_iter = 0; x_iter < size; x_iter++)
    {
        for (u_int y_iter = 0; y_iter < size; y_iter++)
        {
            if (this->boardState[x_iter][y_iter] != bomb)
                continue;
            for (int x_iter_iter = -1; x_iter_iter <= 1; x_iter_iter++)
            {
                index_X = x_iter_iter + x_iter;
                if(!safetyCheck(index_X, 0, size))
                    continue;
                for (int y_iter_iter = -1; y_iter_iter <= 1; y_iter_iter++)
                {
                    if(x_iter_iter == 0 && y_iter_iter == 0)
                        continue;
                    index_Y = y_iter_iter + y_iter;
                    if(!safetyCheck(index_Y, 0, size))
                        continue;
                    if (this->boardState[index_X][index_Y] == bomb)
                        continue;
                    boardState[index_X][index_Y]++;
                }
            }
        }
    }
}

void minesweeper::activateTile(u_int x, u_int y)
{
    if(!safetyCheck(x, 0, size))
        return;
    if(!safetyCheck(y, 0, size))
        return;
    u_int value = boardState[x][y];
    u_int xCoord, yCoord;
    switch(value)
    {
    case 0:
        groupShow(x,y);
        xCoord = 10;
        yCoord = 50;
        spriteVector[x][y].setTextureRect(sf::IntRect(xCoord, yCoord, xCoord+9,yCoord+9));
        return;
    case bomb:
        boardVisible[x][y] = true;
        this->endGame();
        xCoord = 10;
        yCoord = 20;
        break;
    case 1:
        xCoord = 10;
        yCoord = 40;
        break;
    case 2:
        xCoord = 0;
        yCoord = 10;
        break;
    case 3:
        xCoord = 00;
        yCoord = 20;
        break;
    case 4:
        xCoord = 0;
        yCoord = 30;
        break;
    case 5:
        xCoord = 0;
        yCoord = 40;
        break;
    case 6:
        xCoord = 0;
        yCoord = 50;
        break;
    case 7:
        xCoord = 0;
        yCoord = 60;
        break;
    case 8:
        xCoord = 0;
        yCoord = 70;
        break;
    default:
        boardVisible[x][y] = true;
    }
    spriteVector[x][y].setTextureRect(sf::IntRect(xCoord, yCoord, xCoord+10,yCoord+10));
    boardVisible[x][y] = true;
}

void minesweeper::groupShow(u_int x, u_int y)
{
    if(!safetyCheck(x, 0, size))
        return;
    if(!safetyCheck(y, 0, size))
        return;

    if (this->boardVisible[x][y] != 0)
        return;
    this->boardVisible[x][y] = true;

    u_int xIndex, yIndex;
    for (short x_iter = -1; x_iter <= 1; x_iter++)
    {
        for (short y_iter = -1; y_iter <= 1; y_iter++)
        {
            xIndex = x+x_iter;
            yIndex = y+y_iter;
            if(!safetyCheck(xIndex, 0, size))
                continue;
            if(!safetyCheck(yIndex, 0, size))
                continue;
            if (this->boardState[xIndex][yIndex] == 0 && this->boardVisible[xIndex][yIndex] == false)
                groupShow(xIndex, yIndex);
        }
    }

}

void minesweeper::draw()
{
    for (u_int x_iter = 0; x_iter < size; x_iter++)
    {
        for (u_int y_iter = 0; y_iter < size; y_iter++)
        {
            window->draw(spriteVector[x_iter][y_iter]);
        }
    }
}


void minesweeper::endGame()
{
    playing = false;
}

#include <iostream>
void minesweeper::print()
{
    for (u_int x_iter = 0; x_iter < size; x_iter++)
    {
        for (u_int y_iter = 0; y_iter < size; y_iter++)
        {
            if(!safetyCheck(x_iter, 0, size))
                continue;
            if(!safetyCheck(y_iter, 0, size))
                continue;
            if (!boardVisible[x_iter][y_iter])
                std::cout << " ";
            if (boardVisible[x_iter][y_iter])
                std::cout << boardState[x_iter][y_iter];

        }
        std::cout << '\n';
    }
}

void minesweeper::printAnswer()
{
    for (u_int x_iter = 0; x_iter < size; x_iter++)
    {
        for (u_int y_iter = 0; y_iter < size; y_iter++)
        {
            if(!safetyCheck(x_iter, 0, size))
                continue;
            if(!safetyCheck(y_iter, 0, size))
                continue;
            std::cout << boardState[x_iter][y_iter];

        }
        std::cout << '\n';
    }
}


void minesweeper::mouse(u_int x, u_int y)
{
    auto windowSize = this->window->getSize();
    u_int tileLength = ((windowSize.x - this->padding*2) / size);
    u_int tileHeight = ((windowSize.y - this->padding*2) / size);
    u_int x_iter = x / tileLength;
    u_int y_iter = y / tileHeight;
    std::cout << "x:" <<x_iter << '\t' << "y:" << y_iter << '\t' << "Val:" << boardState[x_iter][y_iter] << '\n';
    this->activateTile(x_iter, y_iter);

}


