#include "boardtile.h"

#include <SFML/Graphics/Texture.hpp>
#include <iostream>


boardtile::boardtile(int x, int y, sf::Texture tileTexture)
{
    this->xPos = x;
    this->yPos = y;
    //this->tileSprite.setTexture(tileTexture, true);
    //this->setHighlightDefault();
}

boardtile::~boardtile()
{

    return;
}

bool boardtile::hasUnit()
{
    if (this->aUnit == nullptr)
    {
        return false;
    }
    return true;
}

void boardtile::setTileUnit(boardObject &aUnit)
{
    this->aUnit = &aUnit;
}
void boardtile::clearTile()
{
    this->aUnit = nullptr;
}

int boardtile::getMovement()
{
    if (!this->hasUnit())
    {
        return 0;
    }
    return aUnit->getMovement();
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
    return this->aUnit->getFEN();
}

