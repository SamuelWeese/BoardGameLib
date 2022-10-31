#include "chess.h"
#include <iostream>

int main()
{
    const static int windowSizeHeight = 720;
    const static int windowSizeLength = 720;
    sf::RenderWindow window(sf::VideoMode(windowSizeLength, windowSizeHeight), "SFML window");
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
            case sf::Event::Resized:
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    aBoard.mouseClick(event.mouseButton.x,event.mouseButton.y);
                }
                break;
            }

            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear();

        aBoard.draw();

        window.display();
    }

    return 0;
}
