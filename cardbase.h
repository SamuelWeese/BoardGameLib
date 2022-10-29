#ifndef CARDBASE_H
#define CARDBASE_H
#include <SFML/Graphics.hpp>

enum cardTags { Undead, Ranged, Melee, Rat };


class cardBase
{
    sf::Texture cardBorder;
    sf::Texture cardImage;
    sf::Sprite cardBuilt;
public:
    cardBase();
    void setImage();
    void setFaction();
    void setRarity();
};

#endif // CARDBASE_H
