#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <stdexcept>

#define ASCII_SPACE_DEFAULT_FEN_CHAR 32

class piece
{
    // need to add disallowed values
    // Currently: numerals, ASCII 0-31 (specials like null), space (ascii 32)
    // default char is currently 32
    // leaves ascii 33 to 47 and ascii 58 to 254 available

protected:
    char fenChar;
public:
    sf::Sprite tileSprite;

    piece(); // empty tile piece
    piece(sf::Texture *aTexture); // empty piece constructor
    virtual ~piece(){return;};
    piece(char aChar, sf::Texture *aTexture);
    piece(char aChar, sf::Texture *aTexture, sf::IntRect aRect);
    char getFEN();
    void draw(sf::RenderWindow *aWindow);
    virtual void setSpriteTexture(sf::Texture *aTexture);
    void setSpriteTextureRect(sf::Texture *aTexture, sf::IntRect aRect);
};

#endif // PIECE_H
