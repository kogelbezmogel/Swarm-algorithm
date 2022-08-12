#include "gui.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 600), "");
    window.setFramerateLimit(60);

    GUI gui( sf::Vector2f(1200, 600) );

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                exit(0); // maybe in future would be nice to find couse of error (maybe try x32 instead of 64)
            }

            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "click\n";
                    gui.handleGuiClick(event);
                }
            if (event.type == sf::Event::TextEntered || sf::Event::KeyPressed) {
                gui.handleButtonClick(event);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                gui.handleGuiReleased(event);
                std::cout << "released\n";
            }
        }

        window.clear();
        window.draw(gui);
        window.display();
    }

    return 0;
}