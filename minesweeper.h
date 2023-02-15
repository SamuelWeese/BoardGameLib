#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define bomb 9




class minesweeper
{
    std::vector<std::vector<u_int>>boardState;
    std::vector<std::vector<bool>> boardVisible;
    u_int size;
    u_int bombs;
    bool playing;

    u_int padding;

    sf::RenderWindow *window;
    sf::Texture spriteSheet;
    std::vector<std::vector<sf::Sprite>> spriteVector;
public:
    minesweeper(sf::RenderWindow *aWindow, u_int size = 10, u_int bombs = 10);
    ~minesweeper();
    void createRBoard();
    void seedRBoard();
    void numberBoard();
    void solve();

    void draw();
    void print();
    void printAnswer();

    void mouse(u_int x, u_int y);

    void groupShow(u_int x, u_int y);
    void activateTile(u_int x, u_int y);


    void endGame();

};

#endif // MINESWEEPER_H
