#include "chess.h"
#include <iostream>
#include "minesweeper.h"

int main()
{
    const static int windowSizeHeight = 720;
    const static int windowSizeLength = 720;
    sf::RenderWindow window(sf::VideoMode(windowSizeLength, windowSizeHeight), "SFML window");
    minesweeper aGame(&window, 5, 10);
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
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    //aBoard.mouseChessClick(event.mouseButton.x,event.mouseButton.y);\

                    aGame.mouse(event.mouseButton.x, event.mouseButton.y);
                }
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
