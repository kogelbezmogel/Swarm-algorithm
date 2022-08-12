#ifndef __TEXT_FIELD__
#define __TEXT_FIELD__

#include "control_element.h"
#include <SFML/Graphics.hpp>
#include <string>

class TextField : public ControlElement {

    sf::Text _text_clear;
    sf::Text _text_with_floor;
    sf::Text _text_with_space;
    sf::Text _empty_state_text;
    sf::RectangleShape _body;

    sf::Vector2f _size;
    sf::Vector2f _position;
    std::string _text_string_clear = { "" };
    std::string _text_string_with_floor = { "" };
    std::string _text_string_with_space = { "" };
    sf::Font _font;

    bool _is_empty = { true };
    bool _in_typing_mode = { false };
    int _pointer_number = { 0 };
    mutable int _counter_for_pointer = { 0 };

    public:
        TextField( std::string name, sf::Vector2f pos, sf::Vector2f size, std::string empty_state_string = "..." );
        virtual void draw( sf::RenderTarget& r_trg, sf::RenderStates r_sts ) const override;
        virtual ControlElement* pointer() override;
            
        virtual void clicked() override { _in_typing_mode = true; }
        virtual void released() override { std::cout << "TextField released\n"; }
        void lost_focus() override { _in_typing_mode = false; }
        void textEntered( sf::Event& event );
        void keyPressed( sf::Event& event );

        virtual void setPosition( sf::Vector2f vec ) override;
        virtual sf::Vector2f getPosition() const override;
        virtual sf::Vector2f getSize() const override;
        std::string getString() const;
        bool onMode() const { return _in_typing_mode; }
};


#endif // __TEXT_FIELD__