#ifndef BOARD_H
#define BOARD_H

#include "boardtile.h"

#include <vector>
#include <string>

#define BOARD_LENGTH 8
#define BOARD_HEIGHT 8
#define BOARD_PADDING 10
#define TILE_SCALING 0.95f

class board
{
protected:
    sf::Texture tileTexture;
    const float tileScaleFloat = TILE_SCALING;
    int padding; // in px
    boardtile *selectedTile;
    int windowLength;
    int windowHeight;
    void positionInitial();
    int length;
    int height;
public:
    sf::RenderWindow *aWindow;
    std::vector<std::vector<boardtile>> gameState;
    board(sf::RenderWindow *aWindow, std::string pathToTexture = "", int boardLength = BOARD_LENGTH,
          int boardHeight = BOARD_HEIGHT, int padding = BOARD_PADDING);
    virtual ~board() {return;}
    void setUpInitialBoard();
    void setTileTexture(std::string pathToTexture);
    bool setTileTexture();
    void draw();
    boardtile* mouseClick(int a, int b);
    void clearBoardHighlights();
    std::string generateFEN();
    virtual void inputFEN() {return;} // add default lookup function later
    virtual void initialPosition() {return;}
protected:
    virtual void generateAttackableSquares(boardtile &selectedTile) {return;}
    virtual void moveUnit(int xStartTile, int yStartTile, int xFinalTile, int yFinalTile);

};

#endif // BOARD_H
