#include "boardtile.h"

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

void boardtile::scalePiece()
{
    if (this->aPiece.tileSprite.getTexture() == nullptr) return; // this should never be necessary, but users are users

    int tileLength = this->tileSprite.getTexture()->getSize().x * this->tileSprite.getScale().x;
    if (!tileLength) tileLength = 1;

    int tileHeight = this->tileSprite.getTexture()->getSize().y * this->tileSprite.getScale().y;
    if (!tileHeight) tileHeight = 1;

    int spriteTextureLength = this->aPiece.tileSprite.getTexture()->getSize().x;
    if (!spriteTextureLength) spriteTextureLength = 1;

    int spriteTextureHeight = this->aPiece.tileSprite.getTexture()->getSize().y;
    if (!spriteTextureHeight) spriteTextureHeight = 1;

    float spriteScaleLength = 1.f / ((float)spriteTextureLength / (float)tileLength);

    float spriteScaleHeight = 1.f / ((float)spriteTextureHeight / (float)tileHeight);

    this->aPiece.tileSprite.setScale(spriteScaleLength, spriteScaleHeight);

}

void boardtile::draw(sf::RenderWindow *aWindow)
{
    aWindow->draw(this->tileSprite);
    this->aPiece.draw(aWindow);
}
