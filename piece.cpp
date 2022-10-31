#include "piece.h"

piece::piece()
{
    fenChar = ASCII_SPACE_DEFAULT_FEN_CHAR;
    return;
}

piece::piece(char aChar, sf::Texture *aTexture)
{
    if (aChar < 33 ||
       (aChar < 52 && aChar > 47)) // guarding against bad character setting, see piece.h for reasons
    {
        throw std::runtime_error("Bad Character Value in Piece Constructor.");
    }
    this->fenChar = aChar;
    this->setSpriteTexture(aTexture);
}

piece::piece(char aChar, sf::Texture *aTexture, sf::IntRect aRect)
{
    if (aChar < 33 ||
       (aChar < 52 && aChar > 47)) // guarding against bad character setting, see piece.h for reasons
    {
        throw std::runtime_error("Bad Character Value in Piece Constructor.");
    }
    this->fenChar = aChar;
    this->setSpriteTextureRect(aTexture, aRect);
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

void piece::setSpriteTextureRect(sf::Texture *aTexture, sf::IntRect aRect)
{
    this->tileSprite.setTexture(*aTexture);
    this->tileSprite.setTextureRect(aRect);
}
