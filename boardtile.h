#ifndef BOARDTILE_H
#define BOARDTILE_H

#include "piece.h"
#include <vector>

class boardtile
{
    piece aPiece;
public:

    sf::Sprite tileSprite;
    int xPos;
    int yPos;
    std::vector<bool> flags; // added for utility this can provide, especially with highlighting
    // this is probably a poor design choice, but it is the fast/extendable one
    boardtile(int x , int y);
    ~boardtile();
    bool hasUnit();
    int getMovement();
    void setPiece(piece aPiece);
    void clearTile();
    void setHighlightDefault();
    void setHighlightSelected();
    void setHighlightAttackable();
    void setHighlightMoveable();
    char getFEN(){ return this->aPiece.getFEN();};
    piece getPiece() {return aPiece;};
    void positionChild(); void positionChild(int x, int y);
    void scalePiece();
    void draw(sf::RenderWindow *aWindow); // draw is identical to piece.draw, not sharing class due to file confusion/readability
};

#endif // BOARDTILE_H
