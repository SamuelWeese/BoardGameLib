#ifndef BOARDTILE_H
#define BOARDTILE_H
#include <SFML/Graphics.hpp>
#include "boardobject.h"

#define DEFAULT_TEXTURE

class boardtile
{
    boardObject *aUnit;
public:
    int xPos;
    int yPos;
    sf::Sprite tileSprite; // feeding this needs to be optimized
    boardtile(int x , int y, sf::Texture tileTexture); // this contains hard coded sprite for board
    ~boardtile();
    bool hasUnit();
    int getMovement();
    void setTileUnit(boardObject &aUnit);
    void clearTile();
    void setHighlightDefault();
    void setHighlightSelected();
    void setHighlightAttacked();
    void setHighlightMoveable();
    char getFEN();
};

#endif // BOARDTILE_H
