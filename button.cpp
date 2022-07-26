#include "button.h"

Button::Button( std::string text, sf::Vector2f pos, sf::Vector2f size ) {
    _whole_size = sf::Vector2i( size.x, size.y );

    _font.loadFromFile("arial.ttf");

    _text.setFont(_font);
    _text.setString(text);
    _text.setStyle( sf::Text::Bold );
    _text.setFillColor( sf::Color::Black );

    _body = sf::RectangleShape( sf::Vector2f( size.x - 2 * _outline_thickness, size.y - 2 * _outline_thickness ) );
    _body.setFillColor( sf::Color(200, 200, 200) );
    _body.setOutlineColor( sf::Color(100, 100, 100) );
    _body.setOutlineThickness( _outline_thickness );

    _body.setPosition(pos.x + _outline_thickness, pos.y + _outline_thickness);
    _text.setCharacterSize( size.y / 2 );
    _text.setPosition( pos.x + _outline_thickness + 2, pos.y  + _outline_thickness + 1 );
}


//setters
void Button::setPosition( sf::Vector2i vec ) {
    _body.setPosition( vec.x + _outline_thickness, vec.y + _outline_thickness );
    _text.setPosition( vec.x + _outline_thickness + 2, vec.y + _outline_thickness + 1 );
}

void Button::setFunctionality( std::function<void(void)> fun ) { _fun = fun; }

void Button::clicked() {
    _body.setFillColor( sf::Color(130, 130, 130) );
    _body.setOutlineColor( sf::Color(70, 70, 70) );
    _body.setOutlineThickness( _outline_thickness + 1 );
    if( _fun )
        _fun();
}

void Button::released() {
    _body.setFillColor( sf::Color(200, 200, 200) );
    _body.setOutlineColor( sf::Color(100, 100, 100) );
    _body.setOutlineThickness( _outline_thickness );
    
}



//getters
sf::Vector2i Button::getPosition() const {
    return sf::Vector2i( _body.getPosition().x - _outline_thickness, _body.getPosition().y - _outline_thickness );
}

sf::Vector2i Button::getSize() const {
    return _whole_size;
}

//void Button::setHeight( int y ) { _body.setSize( _body.getSize().x, y ); }
//void Button::setWidth( int x ) { _body.setSize( x, _body.getSize().y ); }
//void Button::setBorderThickness( int arg ) { _body.setOutlineThickness(arg); }

Button* Button::pointer() {
    return new Button(*this);
}

void Button::draw( sf::RenderTarget& r_trg, sf::RenderStates r_sts ) const {
    r_trg.draw( _body, r_sts );
    r_trg.draw( _text, r_sts );
}