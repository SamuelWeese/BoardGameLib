#include "boardtile.h"

#include <iostream>


boardtile::boardtile(int x, int y)//, sf::Texture tileTexture)
{
    this->xPos = x;
    this->yPos = y;
    this->aPiece = piece();
}

boardtile::~boardtile()
{
    return;
}

bool boardtile::hasUnit()
{
    if (this->aPiece.getFEN() == ASCII_SPACE_DEFAULT_FEN_CHAR)
    {
        return false;
    }
    return true;
}

void boardtile::setTileUnit(piece *aUnit)
{
    this->aPiece = *aUnit;
    this->positionChild();
}
void boardtile::clearTile()
{
    this->aPiece = piece();
    this->positionChild();
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
    this->tileSprite.setColor(sf::Color(255,255,255,128));// white with it being 3/4 transparent
}

void boardtile::setHighlightSelected()
{
    this->tileSprite.setColor(sf::Color(255,255,0,128));
}

void boardtile::setHighlightAttacked()
{
    this->tileSprite.setColor(sf::Color(255,0,255,128));
}

void boardtile::setHighlightMoveable()
{
    this->tileSprite.setColor(sf::Color(0,0,255,128));
}

char boardtile::getFEN()
{
    return this->aPiece.getFEN();
}

void boardtile::positionChild()
{
    auto coordinates = this->tileSprite.getPosition();
    this->aPiece.tileSprite.setPosition(coordinates.x, coordinates.y);
}
void boardtile::positionChild(int x, int y)
{
    this->aPiece.tileSprite.setPosition(x, y);
}

void boardtile::draw(sf::RenderWindow *aWindow)
{
    aWindow->draw(this->tileSprite);
    this->aPiece.draw(aWindow);
}
