#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

#define ASCII_SPACE_DEFAULT_FEN_CHAR 32

class piece
{
    // need to add disallowed values
    // Currently: numerals, ASCII 0-31 (specials like null), space (ascii 32)
    // default char is currently 32
    // leaves ascii 33 to 47 and ascii 58 to 254 available
    char fenChar;
    // Visuals
public:
    sf::Sprite tileSprite;
    piece();
    piece(sf::Texture *aTexture);
    piece(sf::Texture *aTexture, char aChar);
    char getFEN();
    void draw(sf::RenderWindow *aWindow);
    void setSpriteTexture(sf::Texture *aTexture);
};

#endif // PIECE_H
