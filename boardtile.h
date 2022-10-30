#ifndef BOARDTILE_H
#define BOARDTILE_H
#include <SFML/Graphics.hpp>
#include "piece.h"

#define DEFAULT_TEXTURE

class boardtile
{
    piece aPiece;
public:
    sf::Sprite tileSprite;
    int xPos;
    int yPos;
    boardtile(int x , int y);//, sf::Texture tileTexture); // this contains hard coded sprite for board
    ~boardtile();
    bool hasUnit();
    int getMovement();
    void setTileUnit(piece *aUnit); // check this, might be cause crash
    void clearTile();
    void setHighlightDefault();
    void setHighlightSelected();
    void setHighlightAttacked();
    void setHighlightMoveable();
    char getFEN();
    void positionChild(); void positionChild(int x, int y);
    void draw(sf::RenderWindow *aWindow); // this should probably share a class with piece
    // draw is identical to piece.draw
};

#endif // BOARDTILE_H
