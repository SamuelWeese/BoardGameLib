#include "boardtile.h"

#include <iostream>


boardtile::boardtile(int x, int y)//, sf::Texture tileTexture)
{
    this->xPos = x;
    this->yPos = y;
    this->aPiece = new piece();
}

boardtile::~boardtile()
{
    return;
}

bool boardtile::hasUnit()
{
    if (this->aPiece->isDefault)
    {
        return false;
    }
    return true;
}

void boardtile::setTileUnit(piece *aUnit)
{
    this->aPiece = aUnit;
}
void boardtile::clearTile()
{
    this->aPiece = new piece();
}

int boardtile::getMovement()
{
    /*
    if (!this->hasUnit())
    {
        return 0;
    }
    //return aUnit->getMovement(); TODO REMOVED MOVEMENT FROM INATE PIECE, REPLACING WITH PASSING ?FUNCTIONS?
    return 0;*/
    return 0;
}
void boardtile::setHighlightDefault()
{
    this->tileSprite.setColor(sf::Color(255,255,255,64));// white with it being 3/4 transparent
}

void boardtile::setHighlightSelected()
{
    this->tileSprite.setColor(sf::Color(255,255,0,64));
}

void boardtile::setHighlightAttacked()
{
    this->tileSprite.setColor(sf::Color(255,0,255,64));
}

void boardtile::setHighlightMoveable()
{
    this->tileSprite.setColor(sf::Color(0,0,255,64));
}

char boardtile::getFEN()
{
    return this->aPiece->getFEN();
}

void boardtile::draw(sf::RenderWindow *aWindow)
{
    aWindow->draw(this->tileSprite);
    if (aPiece == nullptr) return;
    this->aPiece->draw(aWindow);
}
