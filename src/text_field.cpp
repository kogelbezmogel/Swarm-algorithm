#include "text_field.h"
#include <algorithm>

TextField::TextField( std::string name, sf::Vector2f pos, sf::Vector2f size, std::string empty_state_string ) : ControlElement(name) {
    _size = sf::Vector2f( size.x, size.y );
    _position = sf::Vector2f( pos.x, pos.y );
    _font.loadFromFile("Arial.ttf");

    _body.setSize( size );
    _body.setFillColor( sf::Color(255, 255, 255) );
    _body.setPosition(pos);

    _text_clear.setFont(_font);
    _text_clear.setString(_text_string_clear);
    _text_clear.setFillColor( sf::Color(0, 0, 0) );
    _text_clear.setCharacterSize(15);
    _text_clear.setPosition( pos.x + 2, pos.y + 1 );

    _text_with_floor.setFont(_font);
    _text_with_floor.setString(_text_string_clear + "_");
    _text_with_floor.setFillColor( sf::Color(0, 0, 0) );
    _text_with_floor.setCharacterSize(15);
    _text_with_floor.setPosition( pos.x + 2, pos.y + 1 );

    _text_with_space.setFont(_font);
    _text_with_space.setString(_text_string_clear + "  ");
    _text_with_space.setFillColor( sf::Color(0, 0, 0) );
    _text_with_space.setCharacterSize(15);
    _text_with_space.setPosition( pos.x + 2, pos.y + 1 );

    _empty_state_text.setFont(_font);
    _empty_state_text.setString(empty_state_string);
    _empty_state_text.setFillColor( sf::Color(0, 0, 0) );
    _empty_state_text.setCharacterSize(15);
    _empty_state_text.setPosition( pos.x + 2, pos.y + 1 );
}

void TextField::draw( sf::RenderTarget& r_trg, sf::RenderStates r_sts ) const {

    r_trg.draw(_body, r_sts);

    if( _in_typing_mode ) {
        
        if( _counter_for_pointer < 20)
            r_trg.draw(_text_with_space, r_sts);
        else
            r_trg.draw(_text_with_floor, r_sts);
        ++_counter_for_pointer;
        if( _counter_for_pointer > 60 )
            _counter_for_pointer = 0;
    } 
    else {
        if( _is_empty ) {
            r_trg.draw(_empty_state_text, r_sts);
        }
        else {
            r_trg.draw(_text_clear, r_sts);
        }
    }
}

void TextField::textEntered( sf::Event& event ) {
    int typed = event.text.unicode;
    std::string left_part;
    std::string right_part;

    switch (typed) {
        case 8 :
            left_part = _text_string_clear.substr( 0, std::max(_pointer_number - 1, 0) );
            right_part = _text_string_clear.substr( std::min( (int) _text_string_clear.length(), _pointer_number), _text_string_clear.length() );
            
            std::cout << "Backspace \n";
            std::cout << "Left part: (" << left_part << ")\n";
            std::cout << "Right part: (" << right_part << ")\n";
            std::cout << "pointer number: " << _pointer_number << "\n";
            std::cout << "string length: " << _text_string_clear.length() << "\n\n";

            _text_string_clear = left_part + right_part;
            _text_string_with_floor = left_part + "_" + right_part;
            _text_string_with_space = left_part + "  " + right_part;

            _text_clear.setString( _text_string_clear );
            _text_with_floor.setString( _text_string_with_floor );
            _text_with_space.setString( _text_string_with_space );
            
            if( _text_string_clear.length() == 0 )
                _is_empty = true;
            if( _pointer_number > 0 )
                _pointer_number--;
            break;

        case 13 :
            std::cout << "Enter \n";
            break;

        default:
            left_part = _text_string_clear.substr(0, _pointer_number);
            right_part = _text_string_clear.substr( std::min( (int) _text_string_clear.length(), _pointer_number), _text_string_clear.length() );
            
            _text_string_clear = left_part + static_cast<char>(event.text.unicode) + right_part;
            _text_string_with_floor = left_part + static_cast<char>(event.text.unicode) + "_" + right_part;
            _text_string_with_space = left_part + static_cast<char>(event.text.unicode) + "  " + right_part;

            _text_clear.setString( _text_string_clear );
            _text_with_floor.setString( _text_string_with_floor );
            _text_with_space.setString( _text_string_with_space );
            
            _is_empty = false;
            _pointer_number++;
            break;
    }
}

void TextField::keyPressed( sf::Event& event ) {
    int typed = event.key.code;
    std::string left_part;
    std::string right_part;

    switch (typed) {
    case 71 :
        if( _pointer_number > 0)
            _pointer_number--;
        
        left_part = _text_string_clear.substr(0, _pointer_number);
        right_part = _text_string_clear.substr( std::min( (int) _text_string_clear.length(), _pointer_number), _text_string_clear.length() );
        
        _text_string_with_floor = left_part + "_" + right_part;
        _text_string_with_space = left_part + "  " + right_part;

        _text_with_floor.setString( _text_string_with_floor );
        _text_with_space.setString( _text_string_with_space );
        std::cout << "Left key\n";
        break;

    case 72 :
        if( _pointer_number < _text_string_clear.length() )
            _pointer_number++;
        
        left_part = _text_string_clear.substr(0, _pointer_number);
        right_part = _text_string_clear.substr( std::min( (int) _text_string_clear.length(), _pointer_number), _text_string_clear.length() );
        
        _text_string_with_floor = left_part + "_" + right_part;
        _text_string_with_space = left_part + "  " + right_part;

        _text_with_floor.setString( _text_string_with_floor );
        _text_with_space.setString( _text_string_with_space );
        
        std::cout << "Right key\n";
        break;
    default:
        //std::cout << "Doesn't matter\n";
        break;
    }
}

ControlElement* TextField::pointer() {
    return new TextField( *this );
}

void TextField::setPosition( sf::Vector2f vec )  {
    _position = vec;
    _body.setPosition(_position);
    _text_clear.setPosition(_position.x + 2, _position.y + 1);
    _text_with_floor.setPosition(_position.x + 2, _position.y + 1);
    _text_with_space.setPosition(_position.x + 2, _position.y + 1);
    _empty_state_text.setPosition(_position.x + 2, _position.y + 1);
}

sf::Vector2f TextField::getPosition() const {
    return _position;
}

sf::Vector2f TextField::getSize() const  {
    return _size;
}

std::string TextField::getString() const {
    return _text_string_clear;
}