#ifndef BOARD_H
#define BOARD_H
#include <SFML/Window/Mouse.hpp>
#include "boardtile.h"
#include "boardobject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "preloadTextures.h"

#define BOARD_LENGTH 8
#define BOARD_HEIGHT 8
#define BOARD_PADDING 10
#define TILE_SCALING 0.95f
class board
{
    sf::Texture tileTexture;
    const float tileScaleFloat = TILE_SCALING;
    int length;
    int height;
    int padding; // in px
    boardtile *selectedTile;
    int windowLength;
    int windowHeight;
    void positionInitial();
public:
    sf::RenderWindow *aWindow;
    std::vector<std::vector<boardtile>> gameState;
    board(sf::RenderWindow *aWindow, int windowLength, int windowHeight, int boardLength = BOARD_LENGTH, int boardHeight = BOARD_HEIGHT, int padding = BOARD_PADDING);
    ~board();
    void draw();
    int getDistanceFromSquare(boardtile &selectedTile, boardtile &anotherTile);
    void mouseClick(int a, int b);
    void mouseRightClick();
    void resetClick();
    void generateAttackableSquares(boardtile &selectedTile);
    void clearBoardHighlights();
    void moveUnit(int x, int y, int X2, int Y2);
};

#endif // BOARD_H
