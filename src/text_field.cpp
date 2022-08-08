#include "text_field.h"

TextField::TextField( std::string name, sf::Vector2f pos, sf::Vector2f size, std::string empty_state_string ) : ControlElement(name) {
    _size = sf::Vector2f( size.x, size.y );
    _position = sf::Vector2f( pos.x, pos.y );
    _font.loadFromFile("Arial.ttf");

    _body.setSize( size );
    _body.setFillColor( sf::Color(255, 255, 255) );
    _body.setPosition(pos);

    _text.setFont(_font);
    _text.setString(_text_string);
    _text.setFillColor( sf::Color(0, 0, 0) );
    _text.setCharacterSize(15);
    _text.setPosition( pos.x + 2, pos.y + 1 );

    _text_with_pointer.setFont(_font);
    _text_with_pointer.setString(_text_string + "|");
    _text_with_pointer.setFillColor( sf::Color(0, 0, 0) );
    _text_with_pointer.setCharacterSize(15);
    _text_with_pointer.setPosition( pos.x + 2, pos.y + 1 );

    _empty_state_text.setFont(_font);
    _empty_state_text.setString(empty_state_string);
    _empty_state_text.setFillColor( sf::Color(0, 0, 0) );
    _empty_state_text.setCharacterSize(15);
    _empty_state_text.setPosition( pos.x + 2, pos.y + 1 );
}

void TextField::draw( sf::RenderTarget& r_trg, sf::RenderStates r_sts ) const {

    r_trg.draw(_body, r_sts);

    if( _in_typing_mode ) {
        
        if( _counter_for_pointer < 30)
            r_trg.draw(_text, r_sts);
        else
            r_trg.draw(_text_with_pointer, r_sts);
        ++_counter_for_pointer;
        if( _counter_for_pointer > 60 )
            _counter_for_pointer = 0;
    } 
    else {
        if( _is_empty ) {
            r_trg.draw(_empty_state_text, r_sts);
        }
        else {
            r_trg.draw(_text, r_sts);
        }
    }
}

void TextField::buttonClicked( sf::Event& event ) {
    int typed = event.text.unicode;
    switch (typed)
    {
    case char(8) :
        _text_string = _text_string.substr(0, _text_string.length() - 1 );
        _text.setString( _text_string );
        _text_with_pointer.setString( _text_string + "|" );
        if( _text_string.length() == 0 )
        _is_empty = true;
        break;
    default:
        _text_string = _text_string + static_cast<char>(event.text.unicode);
        _text.setString( _text_string );
        _text_with_pointer.setString( _text_string + "|" );
        _is_empty = false;
        break;
    }
}

ControlElement* TextField::pointer() {
    return new TextField( *this );
}

void TextField::setPosition( sf::Vector2f vec )  {
    _position = vec;
    _body.setPosition(_position);
    _text.setPosition(_position.x + 2, _position.y + 1);
    _text_with_pointer.setPosition(_position.x + 2, _position.y + 1);
    _empty_state_text.setPosition(_position.x + 2, _position.y + 1);
}

sf::Vector2f TextField::getPosition() const {
    return _position;
}

sf::Vector2f TextField::getSize() const  {
    return _size;
}

std::string TextField::getString() const {
    return _text_string;
}