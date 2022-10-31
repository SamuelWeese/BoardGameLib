#include "chess.h"

chess::chess(sf::RenderWindow *aWindow, std::string FEN) : board(aWindow)
{
    this->setUpInitialBoard();
}
