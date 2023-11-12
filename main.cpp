#include "chess.h"
#include <iostream>

int main()
{
    const static int windowSizeHeight = 720;
    const static int windowSizeLength = 720;
    sf::RenderWindow window(sf::VideoMode(windowSizeLength, windowSizeHeight), "SFML window");

    window.setFramerateLimit(60);
    chess aBoard(&window);
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
            default:
                aBoard.eventHandler(event);
            }
        }

        window.clear();

        aBoard.draw();

        window.display();
    }

    return 0;
}
