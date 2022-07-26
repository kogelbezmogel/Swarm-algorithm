#include "gui.h"
#include "button.h"
#include "text_field.h"
#include <iostream>



GUI::GUI( sf::Vector2f size ) {
    _main_size = size;
    _display_panel_pos = sf::Vector2f(0, 0);
    _control_panel_pos = sf::Vector2f(0, int(size.y * 4 / 5) );

    Button* load_from_file_button = new Button( "Zaladuj funkjce z pliku", sf::Vector2f(0, 0), sf::Vector2f(150, 20) );
    Button* load_from_hand_button = new Button( "Wpisz funkcje recznie", sf::Vector2f(160, 0), sf::Vector2f(150, 20) );
    
    connect( load_from_file_button, GUI::loadFunctionFromFile );
    connect( load_from_hand_button, GUI::loadFuncitonFromHand );

    TextField* text_field = new TextField( "...", sf::Vector2f(0, 30), sf::Vector2f(200, 20) );
    connect( text_field, GUI::textFieldInput );

    add( load_from_file_button );
    add( load_from_hand_button );
    add( text_field );
    
    //end
}

void GUI::draw(sf::RenderTarget& r_trg, sf::RenderStates r_sts) const {
    sf::RectangleShape draw_panel( sf::Vector2f(_main_size.x, _main_size.y * 4 / 5) );
    sf::RectangleShape control_panel( sf::Vector2f(_main_size.x, _main_size.y / 5) );

    draw_panel.setFillColor( sf::Color(200, 200, 200) );
    draw_panel.setPosition( _display_panel_pos );

    control_panel.setPosition(_control_panel_pos);
    control_panel.setFillColor( sf::Color(25, 25, 25) );

    sf::RectangleShape element( sf::Vector2f(100, 100) );
    element.setFillColor( sf::Color(_tone, _tone, _tone) );
    element.setPosition( 200, 100 );

    r_trg.draw(draw_panel, r_sts);
    r_trg.draw(control_panel, r_sts);

    r_trg.draw(element, r_sts);
    for(  ControlElement* c : _controls )
        r_trg.draw(*c, r_sts);
}

void GUI::add( ControlElement* c_el ) {
    c_el -> setPosition( sf::Vector2i( c_el->getPosition().x, c_el->getPosition().y + _control_panel_pos.y ) );
    _controls.push_back( c_el );
}

void GUI::connect( ControlElement* c_el, void (GUI::*method)() ) {
    _function_map.insert( std::pair<int, void(GUI::*)() > (c_el->getID(), method) );
}

void GUI::handleGuiClick( sf::Event event ) {
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;

    if( y <= _main_size.y * 4 / 5 )
        std::cout << "(" << x << ", " << y << ") it is drawpanel\n";
    else if( y > _main_size.y * 4 / 5 ) 
        std::cout << "(" << x << ", " << y << ") it is controlpanel\n";

    for( ControlElement* c_el : _controls )
        if( checkControl(*c_el, sf::Vector2i(x, y) ) ) {
            c_el -> clicked();
            ( (*this).*(_function_map.at(c_el -> getID())) ) ();
            std::cout << "My tone after clicked() : " << _tone << "\n";
        }
        else {
            c_el -> lost_focus();
        }
}

void GUI::handleGuiReleased( sf::Event event ) {
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;

    for( ControlElement* c_el : _controls )
        if( checkControl(*c_el, sf::Vector2i(x, y) ) )
            c_el -> released();

}


bool GUI::checkControl( const ControlElement& button, sf::Vector2i click_pos ) const {
    sf::Vector2i button_pos = button.getPosition();
    sf::Vector2i button_size = button.getSize();
    bool result = false;
    
    if( click_pos.x >= button_pos.x && click_pos.x <= button_pos.x + button_size.x )
        if( click_pos.y >= button_pos.y && click_pos.y <= button_pos.y + button_size.y )
            result = true;
    return result;
}

void GUI::handleButtonClick( sf::Event& event ) {
    TextField* tf_ptr = nullptr;

    for( auto el : _controls ) {
        tf_ptr = dynamic_cast<TextField*>(el);
        if( tf_ptr ) {
            tf_ptr -> buttonClicked( event );
        }
    }
}

void GUI::loadFuncitonFromHand() {

}

void GUI::loadFunctionFromFile() {

}

void GUI::textFieldInput() {

}

