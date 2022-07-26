//#ifndef __BUTTON__
//#define __BUTTON__
#pragma once

#include "control_element.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button : public ControlElement {

    sf::RectangleShape _body;
    sf::Text _text;
    sf::Font _font;
    sf::Vector2i _whole_size;
    std::function< void(void) > _fun = [](){ std::cout << "I don't have function\n"; };
    int _outline_thickness = { 2 };
    

    public:
        Button( std::string text, sf::Vector2f pos, sf::Vector2f size );
        virtual ~Button() { }

        void clicked() override;
        void released() override;
        void lost_focus() override { }

        void setPosition( sf::Vector2i vec ) override;
        void setFunctionality( std::function< void(void) > fun );
        
        sf::Vector2i getPosition() const override;
        sf::Vector2i getSize() const override;

        //void setHeight( int arg );
        //void setWidth( int arg );
        //void setBorderThickness( int arg );

        virtual Button* pointer() override;
        virtual void draw(sf::RenderTarget& r_trg, sf::RenderStates r_sts ) const override; 
};

//#endif //__BUTTON__