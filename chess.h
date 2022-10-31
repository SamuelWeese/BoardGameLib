#ifndef CHESS_H
#define CHESS_H
#include "board.h"

class chess : public board
{
public:
    explicit chess(sf::RenderWindow *);
};

#endif // CHESS_H
