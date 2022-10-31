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
    if (aChar < 33) // guarding against bad character setting, see piece.h for reasons
    {
        fenChar = ASCII_SPACE_DEFAULT_FEN_CHAR; // same as piece();
        return;
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
