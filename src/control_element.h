//#ifndef __CONTROL_ELEMENT__
//#define __CONTROL_ELEMENT__
#pragma once 

#include <iostream>
#include <SFML/Graphics.hpp>

class ControlElement : public sf::Drawable {

    private:
        int _id;
        std::string _name;
        static int all_elements_number;

    public:
        ControlElement(std::string name) : _name(name) { _id = all_elements_number; ++all_elements_number; }
        virtual ~ControlElement() { }
        virtual ControlElement* pointer() = 0;
        virtual void draw(sf::RenderTarget& r_trg, sf::RenderStates r_sts) const = 0;
        virtual void clicked() { std::cout << "clicked\n"; }
        virtual void released() { std::cout << "released\n"; }
        virtual void lost_focus() = 0;

        virtual void setPosition( sf::Vector2f vec ) = 0;
        int getID() const { return _id; }
        std::string getName() const { return _name; }

        virtual sf::Vector2f getPosition() const  = 0;
        virtual sf::Vector2f getSize() const = 0;
};

//#endif //__CONTROL_ELEMENT__
