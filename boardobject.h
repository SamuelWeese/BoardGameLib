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

    // Visuals
    sf::Sprite tileSprite;

public:
    boardObject();
    int getMovement();
};

#endif // BOARDOBJECT_H
