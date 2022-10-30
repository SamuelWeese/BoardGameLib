#include <SFML/Graphics.hpp>
#include "board.h"

int main()
{
    const static int windowSizeHeight = 720;
    const static int windowSizeLength = 720;
    sf::Texture whitePawn;
    if (!whitePawn.loadFromFile("/tmp/chess.png", sf::IntRect(0, 0, 100, 100))) // arguments for this are
        //("string name", sf::IntRect(first corner of file (0 for full file), 0 (second corner), size of file, size of file))
    {
        exit(1);
        // error...
    }
    sf::RenderWindow window(sf::VideoMode(windowSizeLength, windowSizeHeight), "SFML window");
    board aBoard(&window, windowSizeLength, windowSizeHeight);
    piece aPiece(&whitePawn);
    aPiece.setSpriteTexture(&whitePawn, 100, 100);
    for (int x = 0; x < aBoard.gameState.size(); x++)
    {
        for (int y = 0; y < aBoard.gameState[x].size(); y++)
        {
            aBoard.gameState[x][y].setTileUnit(&aPiece);
        }
    }
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
