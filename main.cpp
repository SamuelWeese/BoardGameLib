#include "chess.h"
#include <iostream>
#include "minesweeper.h"

int main()
{
    const static int windowSizeHeight = 720;
    const static int windowSizeLength = 720;
    sf::RenderWindow window(sf::VideoMode(windowSizeLength, windowSizeHeight), "SFML window");
    minesweeper aGame(&window, 10, 10);
    aGame.createRBoard();
    aGame.printAnswer();
    window.setFramerateLimit(60);
    /*chess aBoard(&window);*/
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                break;
            case sf::Event::MouseButtonPressed:
                aGame.mouse(event);
                break;
            }

            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear();

        aGame.draw();
        //aBoard.draw();

        window.display();
    }

    return 0;
}
