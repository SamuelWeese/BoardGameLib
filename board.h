#ifndef BOARD_H
#define BOARD_H

#include "boardtile.h"

#include <boost/asio.hpp>

#include <iostream>
#include <vector>
#include <string>

#define BOARD_LENGTH 8
#define BOARD_HEIGHT 8
#define BOARD_PADDING 10

class board
{
protected:
    sf::Texture tileTexture;
    int padding; // in px
    boardtile *selectedTile;
    int windowLength;
    int windowHeight;
    void positionInitial();
    int length;
    int height;
public:
    sf::RenderWindow *aWindow;
    std::vector<std::vector<boardtile>> gameState;
    explicit board(sf::RenderWindow *aWindow, std::string pathToTexture = "", int boardLength = BOARD_LENGTH,
          int boardHeight = BOARD_HEIGHT, int padding = BOARD_PADDING);
    virtual ~board() {return;}
    void setUpInitialBoard();
    void setTileTexture(std::string pathToTexture);
    bool setTileTexture();
    void draw();

    void clearBoardHighlights();
    std::string generateFEN();
    virtual void readFEN(std::string) {return;} // add default lookup function later
    virtual void initialPosition() {return;}
    virtual void placePiece(char, int, int) {return;}
    boardtile* mouseClick(int a, int b);

protected:
    virtual void generateAttackableSquares(boardtile &selectedTile) {return;}
    virtual void movePiece(int xStartTile, int yStartTile, int xFinalTile, int yFinalTile);
// networking
private:
    int connectionStatus;
public:
    std::string receive_FEN(boost::asio::ip::tcp::socket & socket);
    void send_FEN(boost::asio::ip::tcp::socket & socket);

};

#endif // BOARD_H
