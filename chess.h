#ifndef CHESS_H
#define CHESS_H
#include "board.h"

#define CHESS_LENGTH 8
#define CHESS_HEIGHT 8

class chess : public board
{
public:
    explicit chess(sf::RenderWindow *aWindow, std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
};

#endif // CHESS_H
