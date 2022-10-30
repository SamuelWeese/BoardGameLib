#include "piece.h"

piece::piece()
{
    isDefault = true;
    return;
}
piece::piece(sf::Texture *aTexture)
{
    this->setSpriteTexture(aTexture);
}

piece::piece(sf::Texture *aTexture, char aChar)
{
    this->fenChar = aChar;
    this->setSpriteTexture(aTexture);
}
void piece::draw(sf::RenderWindow *aWindow)
{
    aWindow->draw(tileSprite);
}

char piece::getFEN()
{
    return this->fenChar;
}

void piece::setSpriteTexture(sf::Texture *aTexture)
{
    this->tileSprite.setTexture(*aTexture);
}
