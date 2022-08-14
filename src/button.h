//#ifndef __BUTTON__
//#define __BUTTON__
#pragma once

#include "control_element.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button : public ControlElement {

    sf::RectangleShape _body;
    sf::RectangleShape _body_bold;
    sf::Text _text;
    sf::Font _font;
    sf::Vector2f _whole_size;
    sf::Vector2f _min_size;
    std::function< void(void) > _fun = [](){ };
    int _outline_thickness = { 2 };

    mutable bool _activated = { false };
    mutable int _counter;

    public:
        Button( std::string text, sf::Vector2f pos, int font_size, sf::Vector2f size = sf::Vector2f(0, 0) );
        virtual ~Button() { }

        void clicked() override;
        void released() override;
        void lost_focus() override { }

        void setPosition( sf::Vector2f vec ) override;
        void setFunctionality( std::function< void(void) > fun );
        
        sf::Vector2f getPosition() const override;
        sf::Vector2f getSize() const override;

        //void setHeight( int arg );
        //void setWidth( int arg );
        //void setBorderThickness( int arg );

        virtual Button* pointer() override;
        virtual void draw(sf::RenderTarget& r_trg, sf::RenderStates r_sts ) const override; 
};

//#endif //__BUTTON__