#ifndef BOARDTILE_H
#define BOARDTILE_H
#include <SFML/Graphics.hpp>
#include "piece.h"

class boardtile
{
    piece aPiece;
public:
    sf::Sprite tileSprite;
    int xPos;
    int yPos;
    boardtile(int x , int y);
    ~boardtile();
    bool hasUnit();
    int getMovement();
    void setPiece(piece aPiece);
    void clearTile();
    void setHighlightDefault();
    void setHighlightSelected();
    void setHighlightAttacked();
    void setHighlightMoveable();
    char getFEN(){ return this->aPiece.getFEN();};
    piece getPiece() {return this->aPiece;}
    void positionChild(); void positionChild(int x, int y);
    void draw(sf::RenderWindow *aWindow); // draw is identical to piece.draw, not sharing class due to file confusion/readability
};

#endif // BOARDTILE_H
