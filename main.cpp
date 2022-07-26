#include "button.h"
#include "gui.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <experimental/filesystem>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 600), "");
    window.setFramerateLimit(60);

    GUI gui( sf::Vector2f(1200, 600) );

    for( const auto& file : std::filesystem::recursive_directory_iterator("../") )
        std::cout << file.path() << "\n\n";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if( event.type == sf::Event::MouseButtonPressed)
                if(event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "click\n";
                    gui.handleGuiClick( event );
                }
            if( event.type == sf::Event::TextEntered) { 
                std::cout << static_cast<char> (event.text.unicode) << "\n";
                gui.handleButtonClick( event );
            }
            if( event.type == sf::Event::MouseButtonReleased ) {
                gui.handleGuiReleased( event );
                std::cout << "released\n";
            }


            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(gui);
        window.display();
    }

    return 0;
}