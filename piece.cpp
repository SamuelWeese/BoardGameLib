#include "piece.h"

piece::piece()
{
    fenChar = ASCII_SPACE_DEFAULT_FEN_CHAR;
    return;
}
piece::piece(sf::Texture *aTexture)
{
    this->setSpriteTexture(aTexture);
}


piece::piece(sf::Texture *aTexture, char aChar)
{
    if (aChar < 33 ||
       (aChar < 52 && aChar > 47)) // guarding against bad character setting, see piece.h for reasons
    {
        throw std::runtime_error("Bad Character Value in Piece Constructor.");
    }
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
