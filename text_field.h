#ifndef __TEXT_FIELD__
#define __TEXT_FIELD__

#include "control_element.h"
#include <SFML/Graphics.hpp>
#include <string>

class TextField : public ControlElement {

    sf::Vector2i _size;
    sf::Vector2i _position;
    std::string _text = { "" };
    sf::Font _font;

    bool _is_empty = { true };
    bool _in_typing_mode = { false };
    mutable int _counter_for_pointer = { 0 };

    public:
        TextField( std::string null_state_string, sf::Vector2f pos, sf::Vector2f size );
        virtual void draw( sf::RenderTarget& r_trg, sf::RenderStates r_sts ) const override;
        virtual ControlElement* pointer() override;
            
        virtual void clicked() override { _in_typing_mode = true; }
        virtual void released() override { std::cout << "TextField released\n"; }
        void lost_focus() override { _in_typing_mode = false; }
        void buttonClicked( sf::Event& event );

        virtual void setPosition( sf::Vector2i vec ) override;
        virtual sf::Vector2i getPosition() const override;
        virtual sf::Vector2i getSize() const override;
};


#endif // __TEXT_FIELD__