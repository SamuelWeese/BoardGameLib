#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

class piece
{
    // need to add disallowed values
    // Currently: numerals, ASCII 0-31 (specials like null), space (ascii 32)
    // leaves ascii 33 to 47 and ascii 58 to 254 available
    char fenChar;
    // Visuals
public:
    bool isDefault;
    sf::Sprite tileSprite;
    piece();
    piece(sf::Texture *aTexture);
    piece(sf::Texture *aTexture, char aChar);
    char getFEN();
    void draw(sf::RenderWindow *aWindow);
    void setSpriteTexture(sf::Texture *aTexture);
};

#endif // PIECE_H
