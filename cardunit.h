#ifndef CARDUNIT_H
#define CARDUNIT_H
#include "cardbase.h"
#include <string>
#include <vector>

template <class aFunctionObject>
class cardUnit : public cardBase
{
    // mechanics
    int movement;
    int attack;
    int health;
    int armor;
    int range;
    aFunctionObject *specialStuff;
    std::vector<cardTags> tags;
    // names and stuff
    std::string generateDescription();
    std::string name;
    std::string description;
    std::string type;
public:
    cardUnit(sf::Texture cardImage, std::string cardName, int movement, int attack, int health, int armor, int range, aFunctionObject &specialStuff = nullptr);

};

#endif // CARDUNIT_H
