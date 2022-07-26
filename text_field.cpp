#include "text_field.h"

TextField::TextField( std::string null_state_string, sf::Vector2f pos, sf::Vector2f size ) {
    _size = sf::Vector2i( size.x, size.y );
    _position = sf::Vector2i( pos.x, pos.y );
    _font.loadFromFile("arial.ttf");
}

void TextField::draw( sf::RenderTarget& r_trg, sf::RenderStates r_sts ) const {
    sf::RectangleShape field( sf::Vector2f( _size.x, _size.y ) );
    sf::Text text1( _text, _font, 15 );
    sf::Text text2( _text + "|", _font, 15);
    sf::Text empty_text( "...", _font, 15 );

    field.setFillColor( sf::Color(255, 255, 255) );
    text1.setFillColor( sf::Color(0, 0, 0) );
    text2.setFillColor( sf::Color(0, 0, 0) );
    empty_text.setFillColor( sf::Color(0, 0, 0) );

    field.setPosition( _position.x, _position.y );
    text1.setPosition( _position.x + 2, _position.y);
    text2.setPosition( _position.x + 2, _position.y);
    empty_text.setPosition(_position.x + 2, _position.y);

    r_trg.draw(field, r_sts);

    if( _in_typing_mode ) {
        
        if( _counter_for_pointer < 30)
            r_trg.draw(text1, r_sts);
        else
            r_trg.draw(text2, r_sts);
        ++_counter_for_pointer;
        if( _counter_for_pointer > 60 )
            _counter_for_pointer = 0;
    } 
    else {
        if( _is_empty ) {
            r_trg.draw(empty_text, r_sts);
        }
        else {
            r_trg.draw(text1, r_sts);
        }
    }
}

void TextField::buttonClicked( sf::Event& event ) {
    int typed = event.text.unicode;
    switch (typed)
    {
    case char(8) :
        _text = _text.substr(0, _text.length() - 1 );
        if( _text.length() == 0 )
        _is_empty == true;
        break;
    default:
        _text = _text + static_cast<char>(event.text.unicode);
        _is_empty = false;
        break;
    }
}

ControlElement* TextField::pointer() {
    return new TextField( *this );
}

void TextField::setPosition( sf::Vector2i vec )  {
    _position = vec;
}

sf::Vector2i TextField::getPosition() const {
    return _position;
}

sf::Vector2i TextField::getSize() const  {
    return _size;
}