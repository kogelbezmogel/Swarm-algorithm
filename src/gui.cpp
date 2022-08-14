#include "gui.h"
#include "button.h"
#include "text_field.h"
#include <iostream>



GUI::GUI( sf::Vector2f size ) {

    _reader = new AnaliticFunctionReader();
    _main_size = size;
    _display_panel_pos = sf::Vector2f(0, 0);
    _control_panel_pos = sf::Vector2f(0, int(size.y * 4 / 5) );
    _plot = new FunctionPlot2D();

    Button* load_from_file_button = new Button( "Zaladuj funkjce z pliku", sf::Vector2f(0, 0), 15 );
    Button* load_from_hand_button = new Button( "Wpisz funkcje recznie", sf::Vector2f(400, 0), 15 );
    Button* draw_plot_button = new Button( "Narysuj funkcje", sf::Vector2f(0, 50), 15 );
    TextField* text_field = new TextField( "Pole tekstowe z funkcja", sf::Vector2f(0, 100), sf::Vector2f(200, 20) );

    connect( load_from_file_button, &GUI::loadFunctionFromFile );
    connect( load_from_hand_button, &GUI::loadFuncitonFromHand );
    connect( draw_plot_button, &GUI::drawFunction );
    connect( text_field, &GUI::textFieldInput );

    add( load_from_file_button );
    add( load_from_hand_button );
    add( text_field );
    add( draw_plot_button ); 
    //end
}

GUI::~GUI() {
    if( _plot ) delete _plot;
    if( _reader ) delete _reader;
    for( ControlElement* el : _controls )
        delete el;
}

void GUI::draw(sf::RenderTarget& r_trg, sf::RenderStates r_sts) const {
    sf::RectangleShape draw_panel( sf::Vector2f(_main_size.x, _main_size.y * 4 / 5) );
    sf::RectangleShape control_panel( sf::Vector2f(_main_size.x, _main_size.y / 5) );

    draw_panel.setFillColor( sf::Color(200, 200, 200) );
    draw_panel.setPosition( _display_panel_pos );

    control_panel.setPosition(_control_panel_pos);
    control_panel.setFillColor( sf::Color(25, 25, 25) );

    r_trg.draw(draw_panel, r_sts);
    r_trg.draw(control_panel, r_sts);
    r_trg.draw(*_plot);

    for(  ControlElement* c : _controls )
        r_trg.draw(*c, r_sts);
}

void GUI::add( ControlElement* c_el ) {
    c_el -> setPosition( sf::Vector2f( c_el->getPosition().x, c_el->getPosition().y + _control_panel_pos.y ) );
    _controls.push_back( c_el );
    _call_function_by_name.insert( std::pair<std::string, ControlElement*>(c_el -> getName(), c_el) );
}

void GUI::connect( ControlElement* c_el, void (GUI::*method)() ) {
    _function_map.insert( std::pair<int, void(GUI::*)() > (c_el->getID(), method) );
}

void GUI::handleGuiClick( sf::Event event ) {
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;

    for( ControlElement* c_el : _controls )
        if( checkControl(*c_el, sf::Vector2f(x, y) ) ) {
            std::cout << "Clicked: " << c_el -> getName() << "\n";
            c_el -> clicked();
            ( (*this).*(_function_map.at(c_el -> getID())) ) ();
        }
        else {
            c_el -> lost_focus();
        }
}

void GUI::handleGuiReleased( sf::Event event ) {
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;

    for( ControlElement* c_el : _controls )
        if( checkControl(*c_el, sf::Vector2f(x, y) ) )
            c_el -> released();
}


bool GUI::checkControl( const ControlElement& button, sf::Vector2f click_pos ) const {
    sf::Vector2f button_pos = button.getPosition();
    sf::Vector2f button_size = button.getSize();
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
        if( tf_ptr && tf_ptr->onMode() ) {
            if( event.type == sf::Event::KeyPressed )        
                tf_ptr -> keyPressed( event );
            else if( event.type == sf::Event::TextEntered )
                tf_ptr -> textEntered( event );
        }
    }
}

void GUI::loadFuncitonFromHand() {
    std::cout << "Function loadFunctionFromHand\n";
}

void GUI::loadFunctionFromFile() {
    std::cout << "Function loadFunctionFromFile\n";
    std::ofstream f("Well.txt");
    f.open("Well.txt", std::ios::out );
    f << "hey";
    f.flush();
    f.close();
}

void GUI::textFieldInput() {

}

void GUI::drawFunction() {
    std::cout << "Function drawFunction\n";
    std::string fun_string = dynamic_cast<TextField*>(_call_function_by_name["Pole tekstowe z funkcja"]) -> getString();
    _reader -> setLine( fun_string );
    _reader -> convertSchema();
    std::cout << "Function: " << fun_string << "\n";

    std::vector< std::pair<double, double> > fun_points;
    for(double i = -5; i < 5;) {
        fun_points.push_back( std::pair<double, double>(i, _reader -> function_value_in_point(i)) );
        i += 0.01;
    }

    _plot = new FunctionPlot2D( fun_points, 5, -5, 5, -5, sf::Vector2f(800, 400) );

}

