#include "button.h"

Button::Button(std::string text, sf::Vector2f pos, int font_size, sf::Vector2f size ): ControlElement(text) {

    _font.loadFromFile("Arial.ttf");

    _whole_size = sf::Vector2f( size.x, size.y );
    _min_size = sf::Vector2f( font_size * text.length() * 3. / 5 + 4, font_size * 1.8 );
    
    if( _min_size.x >_whole_size.x || _min_size.y > _whole_size.y ) {
        _whole_size = sf::Vector2f( std::max(_min_size.x, _whole_size.x), std::max(_min_size.y, _whole_size.y) );
    }

    _text.setFont(_font);
    _text.setString(text);
    _text.setStyle( sf::Text::Bold );
    _text.setFillColor( sf::Color::Black );

    _body = sf::RectangleShape( sf::Vector2f( _whole_size.x - 2 * _outline_thickness, _whole_size.y - 2 * _outline_thickness ) );
    _body.setFillColor( sf::Color(200, 200, 200) );
    _body.setOutlineColor( sf::Color(100, 100, 100) );
    _body.setOutlineThickness( _outline_thickness );

    _body.setPosition(pos.x + _outline_thickness, pos.y + _outline_thickness);
    _text.setCharacterSize( font_size );
    _text.setPosition( pos.x + _outline_thickness, pos.y  + _outline_thickness );

    _body_bold.setFillColor( sf::Color(130, 130, 130) );
    _body_bold.setOutlineColor( sf::Color(70, 70, 70) );
    _body_bold.setOutlineThickness( _outline_thickness + 1 );

}


//setters
void Button::setPosition( sf::Vector2f vec ) {
    _body.setPosition( vec.x + _outline_thickness, vec.y + _outline_thickness );
    _text.setPosition( vec.x + _outline_thickness + 4, vec.y + _outline_thickness + (_whole_size.y - _min_size.y) / 2 );
}

void Button::setFunctionality( std::function<void(void)> fun ) { _fun = fun; }


void Button::clicked() {
    _activated = true;
}

void Button::released() {
    //_body.setFillColor( sf::Color(200, 200, 200) );
    //_body.setOutlineColor( sf::Color(100, 100, 100) );
    //_body.setOutlineThickness( _outline_thickness );
}



//getters
sf::Vector2f Button::getPosition() const {
    return sf::Vector2f( _body.getPosition().x - _outline_thickness, _body.getPosition().y - _outline_thickness );
}

sf::Vector2f Button::getSize() const {
    return _whole_size;
}

//void Button::setHeight( int y ) { _body.setSize( _body.getSize().x, y ); }
//void Button::setWidth( int x ) { _body.setSize( x, _body.getSize().y ); }
//void Button::setBorderThickness( int arg ) { _body.setOutlineThickness(arg); }

Button* Button::pointer() {
    return new Button(*this);
}

void Button::draw( sf::RenderTarget& r_trg, sf::RenderStates r_sts ) const {
    if( _activated ) {
        r_trg.draw( _body_bold, r_sts );

        if( _counter < 15 ) ++_counter;
        else { _activated = false; _counter = 0; }
    }
    else
        r_trg.draw(_body, r_sts);
    r_trg.draw( _text, r_sts );
}