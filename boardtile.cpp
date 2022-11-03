#include "boardtile.h"

boardtile::boardtile(int x, int y)//, sf::Texture tileTexture)
{
    this->xPos = x;
    this->yPos = y;
    this->aPiece = piece();
    this->textureHeight = -1;
    this->textureLength = -1;
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

void boardtile::setTextureByRect(sf::IntRect aRect)
{
    int anX = this->tileSprite.getGlobalBounds().width; // TODO, this currently doesn't actually return the correct size
    int anY = this->tileSprite.getGlobalBounds().height;
    tileSprite.setTextureRect(aRect);
    this->scaleTile(anX, anY);
}
void boardtile::setPiece(piece aPiece)
{
    this->aPiece = aPiece;
    this->positionChild();
    this->scalePiece();
}
void boardtile::clearTile()
{
    this->aPiece = piece();
    this->positionChild();
}

void boardtile::setHighlightDefault()
{
    this->tileSprite.setColor(sf::Color(255,255,255,128));// white with it being 1/2 transparent
}

void boardtile::setHighlightSelected()
{
    this->tileSprite.setColor(sf::Color(255,255,0,128));
}

void boardtile::setHighlightAttackable()
{
    this->tileSprite.setColor(sf::Color(255,0,255,128));
}

void boardtile::setHighlightMoveable()
{
    this->tileSprite.setColor(sf::Color(0,0,255,128));
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

#include <iostream>

void boardtile::scaleTile(int x, int y)// this scales tile to x by y pixels
{
    if (this->tileSprite.getTexture() == nullptr) return; // this should never be necessary, but users are users
    int tileLength, tileHeight;
    tileLength = this->tileSprite.getGlobalBounds().width;
    if (!tileLength) tileLength = 1;
    tileHeight = this->tileSprite.getGlobalBounds().height;
    if (!tileHeight) tileHeight = 1;

    float tileScaleLength = (float)x / (float)tileLength;
    float tileScaleHeight = (float)y / (float)tileHeight;
    this->tileSprite.scale(tileScaleLength, tileScaleHeight);
    this->scalePiece();
}

void boardtile::scalePiece()
{
    if (this->aPiece.tileSprite.getTexture() == nullptr) return; // this should never be necessary, but users are users

    int tileLength = this->tileSprite.getGlobalBounds().width;
    int tileHeight = this->tileSprite.getGlobalBounds().height;

    // divide by zero is not defined to throw, I believe it return NaN
    int spriteTextureLength = this->aPiece.getLength();
    if (!spriteTextureLength) spriteTextureLength = 1;

    int spriteTextureHeight = this->aPiece.getHeight();
    if (!spriteTextureHeight) spriteTextureHeight = 1;

    float spriteScaleLength = (float)tileLength / (float)spriteTextureLength;
    float spriteScaleHeight = (float)tileHeight / (float)spriteTextureHeight;

    this->aPiece.tileSprite.setScale(spriteScaleLength, spriteScaleHeight);

}

void boardtile::draw(sf::RenderWindow *aWindow)
{
    aWindow->draw(this->tileSprite);
    this->aPiece.draw(aWindow);
}
