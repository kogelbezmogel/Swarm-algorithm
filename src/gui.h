//#ifndef __GUI__
//#define __GUI__
#pragma once

#include "control_element.h"
#include "button.h"
#include "plot_classes.h"
#include "AnaliticFunctionReader.h"
#include <SFML/Graphics.hpp>
#include <memory>

class GUI : public sf::Drawable {

    sf::Vector2f _main_pos = {0, 0};
    sf::Vector2f _main_size = {0, 0};
    sf::Vector2f _display_panel_pos = {0 ,0};
    sf::Vector2f _control_panel_pos = {0 ,0};
    sf::Vector2f _control_panel_size = {0, 0};
    sf::Vector2f _display_panel_size = {0, 0};

    AnaliticFunctionReader* _reader;
    FunctionPlot2D* _plot;

    std::vector< ControlElement*> _controls;
    std::map<int, void (GUI::*)()> _function_map; //it maps int (which is element id) to GUI method
    std::map<std::string, ControlElement*> _call_function_by_name;

    protected:
        bool checkControl( const ControlElement& button, sf::Vector2f click_pos ) const;
        void add(  ControlElement* c_el );
        void connect( ControlElement* c_el, void (GUI::*method)() );

    public:
        GUI( sf::Vector2f size );
        ~GUI();
        virtual void draw(sf::RenderTarget& r_trg, sf::RenderStates r_sts) const override;

        void handleGuiClick( sf::Event event );
        void handleGuiReleased( sf::Event event );
        void handleButtonClick( sf::Event& event );

        //buttons functions
        void loadFunctionFromFile();
        void loadFuncitonFromHand();
        void textFieldInput();
        void drawFunction();
};

//#endif //__GUI__