#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H
#include "cardbase.h"

class boardObject
{
    int movement;
    int attack;
    int health;
    int armor;
    int range;
    // need to add disallowed values
    // Currently: numerals, ASCII 0-31 (specials like null), space (ascii 32)
    // leaves ascii 33 to47 and ascii 58 to 254 available
    char fenChar;
    // Visuals
    sf::Sprite tileSprite;

public:
    boardObject();
    int getMovement();
    char getFEN();
};

#endif // BOARDOBJECT_H
